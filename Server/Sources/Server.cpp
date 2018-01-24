//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#include "Server.hpp"

http::Server::Server(const std::string& address, const std::string& port, const std::string& doc_root)
  : _io_service(), _signals(this->_io_service), _acceptor(this->_io_service), _connection_manager(), _socket(this->_io_service), _request_handler(doc_root) {
  this->_signals.add(SIGINT);
  this->_signals.add(SIGTERM);
#if defined(SIGQUIT)
  this->_signals.add(SIGQUIT);
#endif

  do_await_stop();

  boost::asio::ip::tcp::resolver resolver(this->_io_service);
  boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve({address, port});
  this->_acceptor.open(endpoint.protocol());
  this->_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
  this->_acceptor.bind(endpoint);
  this->_acceptor.listen();

  do_accept();
}

void http::Server::run() {
  this->_io_thread = boost::thread(boost::bind(&boost::asio::io_service::run, &this->_io_service));
}

void http::Server::stop() {
  this->_io_service.stop();
  this->_io_thread.join();
}

void http::Server::do_accept() {
  this->_acceptor.async_accept(this->_socket,
      [this](boost::system::error_code ec) {
        if (!this->_acceptor.is_open()) {
          return;
        }

        if (!ec) {
          this->_connection_manager.start(std::make_shared<connection>(
              std::move(this->_socket), this->_connection_manager, this->_request_handler));
        }

        do_accept();
      });
}

void http::Server::do_await_stop() {
  this->_signals.async_wait(
      [this](boost::system::error_code, int) {
        this->_acceptor.close();
        this->_connection_manager.stop_all();
      });
}


direct::Server *direct::Server::Singleton;

direct::Server::Server(const boost::asio::ip::tcp::endpoint& endpoint)
: _io_service(), _endpoint(endpoint), _signals(this->_io_service), _acceptor(this->_io_service, endpoint), _socket(this->_io_service) {
  direct::Server::Singleton = this;
  this->_signals.add(SIGINT);
  this->_signals.add(SIGTERM);
#if defined(SIGQUIT)
  this->_signals.add(SIGQUIT);
#endif

  do_await_stop();

  do_accept();
}

void direct::Server::run() {
  this->_io_thread = boost::thread(boost::bind(&boost::asio::io_service::run, &this->_io_service));
}

void direct::Server::stop() {
  this->_io_service.stop();
  this->_io_thread.join();
}

void direct::Server::broadcast(const std::string &message) {
  for (auto &session: this->_sessions) {
    session->deliver(message);
  }
}

void direct::Server::do_accept() {
  this->_acceptor.async_accept(this->_socket,
      [this](boost::system::error_code ec) {
        switch (ec.value() ) {
          case boost::system::errc::success: {
            this->_sessions.push_back(std::make_shared<direct::Session>(std::move(this->_socket)));
            this->_sessions.back()->start();
            break;
          }
          default: {

          }
          break;
        }

        do_accept();
      });
}

void direct::Server::do_await_stop() {
  this->_signals.async_wait(
      [this](boost::system::error_code, int) {
        this->_acceptor.close();
      });
}
