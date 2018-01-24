//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#ifndef HTTP_CONNECTION_MANAGER_HPP
#define HTTP_CONNECTION_MANAGER_HPP

#include <set>
#include "Connection.hpp"

namespace http {

  class ConnectionManager {

  public:
    ConnectionManager(const ConnectionManager&) = delete;
    ConnectionManager& operator=(const ConnectionManager&) = delete;

    ConnectionManager();

    void start(connection_ptr c);
    void stop(connection_ptr c);
    void stop_all();

  private:
    std::set<connection_ptr> connections_;

  };

} // namespace http

#endif // HTTP_CONNECTION_MANAGER_HPP
