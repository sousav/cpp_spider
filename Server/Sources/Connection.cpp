//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#include "Connection.hpp"
#include "ConnectionManager.hpp"

http::connection::connection(boost::asio::ip::tcp::socket socket, ConnectionManager& manager, RequestHandler& handler)
  : _socket(std::move(socket)), _connection_manager(manager), _request_handler(handler)
{
}

void http::connection::start() {
  do_read();
}

void http::connection::stop() {
  this->_socket.close();
}

void http::connection::do_read() {
  this->_buffer.fill(0);
  auto self(shared_from_this());
  this->_socket.async_read_some(boost::asio::buffer(this->_buffer),
      [this, self](boost::system::error_code ec, std::size_t bytes_transferred) {
        if (!ec) {
          RequestParser::result_type result;
          std::tie(result, std::ignore) = this->_request_parser.parse(this->_request, this->_buffer.data(), this->_buffer.data() + bytes_transferred);

          if (result == RequestParser::good) {
            this->_request_handler.handle_request(this->_request, this->_reply, std::string(this->_buffer.data()).substr(std::string(this->_buffer.data()).find("\r\n\r\n") + 4));
            do_write();
          } else if (result == RequestParser::bad) {
            this->_reply = Reply::stock_reply(Reply::bad_request);
            do_write();
          } else {
            do_read();
          }
        } else if (ec != boost::asio::error::operation_aborted) {
          this->_connection_manager.stop(shared_from_this());
        }
      });
}

void http::connection::do_write() {
  auto self(shared_from_this());
  boost::asio::async_write(this->_socket, this->_reply.to_buffers(),
      [this, self](boost::system::error_code ec, std::size_t) {
        if (!ec) {
          boost::system::error_code ignored_ec;
          this->_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
            ignored_ec);
        }

        if (ec != boost::asio::error::operation_aborted) {
          this->_connection_manager.stop(shared_from_this());
        }
      });
}
