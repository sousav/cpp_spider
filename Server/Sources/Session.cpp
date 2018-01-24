//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#include "Session.hpp"

direct::Session::Session(boost::asio::ip::tcp::socket socket) : _socket(std::move(socket)) {

}

void direct::Session::start() {
  do_read_header();
}

void direct::Session::deliver(const direct::Message& msg) {
  bool write_in_progress = !this->_write_msgs.empty();
  this->_write_msgs.push_back(msg);
  if (!write_in_progress) {
    do_write();
  }
}

void direct::Session::do_read_header() {
  auto self(shared_from_this());
  std::memset(this->_read_msg.data(), '\0', direct::Message::header_length + direct::Message::max_body_length);
  boost::asio::async_read(this->_socket, boost::asio::buffer(this->_read_msg.data(), direct::Message::header_length),
      [this, self](boost::system::error_code ec, std::size_t /*length*/) {
        if (!ec && this->_read_msg.decode_header()) {
          do_read_body();
        } else {
          //TODO ERROR
        }
      });
}

void direct::Session::do_read_body() {
  auto self(shared_from_this());
  boost::asio::async_read(this->_socket, boost::asio::buffer(this->_read_msg.body(), this->_read_msg.body_length()),
      [this, self](boost::system::error_code ec, std::size_t /*length*/) {
        if (!ec) {
          direct::AContent *content = static_cast<direct::AContent *>(direct::IContent::IContentCreator(this->_read_msg.body()));
          BddEndPoint::setIPOfClient(this->_socket.remote_endpoint().address().to_string(), content->getClientID());

          Message output = this->_apiHandler.resolve(this->_read_msg.body());
          std::cout << "sending : " << output.body() << std::endl << std::endl;
          this->deliver(output);
          do_read_header();
        } else {
            //TODO ERROR
        }
      });
}

void direct::Session::do_write() {
  auto self(shared_from_this());
  boost::asio::async_write(this->_socket, boost::asio::buffer(this->_write_msgs.front().data(), this->_write_msgs.front().length()),
      [this, self](boost::system::error_code ec, std::size_t /*length*/) {
        if (!ec) {
          this->_write_msgs.pop_front();
          if (!this->_write_msgs.empty()) {
            do_write();
          }
        } else {
          //TODO ERROR
        }
      });
}
