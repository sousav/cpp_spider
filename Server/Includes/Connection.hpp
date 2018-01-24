//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#ifndef HTTP_CONNECTION_HPP
#define HTTP_CONNECTION_HPP

#include <array>
#include <memory>
#include <boost/asio.hpp>
#include <utility>
#include <vector>

#include "Reply.hpp"
#include "Request.hpp"
#include "RequestParser.hpp"
#include "RequestHandler.hpp"

namespace http {

  class ConnectionManager;

  class connection : public std::enable_shared_from_this<connection> {

  public:
    connection(const connection&) = delete;
    connection& operator=(const connection&) = delete;

    explicit connection(boost::asio::ip::tcp::socket socket, ConnectionManager& manager, RequestHandler& handler);

    void start();
    void stop();

  private:
    void do_read();
    void do_write();

    boost::asio::ip::tcp::socket _socket;
    ConnectionManager& _connection_manager;
    RequestHandler& _request_handler;
    std::array<char, 8192> _buffer;
    Request _request;
    RequestParser _request_parser;
    Reply _reply;
  };

  typedef std::shared_ptr<connection> connection_ptr;

} // namespace http

#endif // HTTP_CONNECTION_HPP
