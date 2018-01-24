//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#ifndef SESSION_HPP_
#define SESSION_HPP_

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <cstdlib>
#include <deque>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include "ApiHandler.hpp"
#include "Message.hpp"
#include "AContent.hpp"
#include "Database/BddEndPoint.hpp"

namespace direct {

  typedef std::deque<direct::Message> MessageQueue;

  class Session : public std::enable_shared_from_this<Session> {

  public:
    Session(boost::asio::ip::tcp::socket socket);

    void start();
    void deliver(const direct::Message& msg);

  private:
    void do_read_header();
    void do_read_body();
    void do_write();

    boost::asio::ip::tcp::socket _socket;
    direct::Message _read_msg;
    MessageQueue _write_msgs;
    ApiHandler _apiHandler;

  };

} // namespace direct

#endif // SESSION_HPP_
