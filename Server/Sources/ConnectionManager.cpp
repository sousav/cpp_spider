//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#include "ConnectionManager.hpp"

http::ConnectionManager::ConnectionManager()
{
}

void http::ConnectionManager::start(connection_ptr c) {
  connections_.insert(c);
  c->start();
}

void http::ConnectionManager::stop(connection_ptr c) {
  connections_.erase(c);
  c->stop();
}

void http::ConnectionManager::stop_all() {
  for (auto c: connections_)
    c->stop();
  connections_.clear();
}
