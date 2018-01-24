//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <string>
#include <map>
#include <memory>
#include <signal.h>
#include <utility>

#include "Connection.hpp"
#include "ConnectionManager.hpp"
#include "RequestHandler.hpp"
#include "Session.hpp"

namespace http {

  class Server {

  public:
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    explicit Server(const std::string& address, const std::string& port, const std::string& doc_root);

    void run();
    void stop();

  private:
    void do_accept();
    void do_await_stop();

    boost::asio::io_service _io_service;
    boost::asio::signal_set _signals;
    boost::thread _io_thread;
    boost::asio::ip::tcp::acceptor _acceptor;
    ConnectionManager _connection_manager;
    boost::asio::ip::tcp::socket _socket;
    RequestHandler _request_handler;

  };

} // namespace http


namespace direct {

  class Server {

  public:
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    explicit Server(const boost::asio::ip::tcp::endpoint& endpoint);

    void run();
    void stop();

    void broadcast(const std::string &message);

  public: static Server *Singleton;

  private:
    void do_accept();
    void do_await_stop();

    boost::asio::io_service _io_service;
    boost::asio::signal_set _signals;
    boost::thread _io_thread;
    boost::asio::ip::tcp::acceptor _acceptor;
    boost::asio::ip::tcp::socket _socket;
    boost::asio::ip::tcp::endpoint _endpoint;

    std::vector<std::shared_ptr<direct::Session>> _sessions;

  };

} // namespace direct

#endif // HTTP_SERVER_HPP
