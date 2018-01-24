//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#ifndef API_HANDLER_HPP_
#define API_HANDLER_HPP_

#include <string>
#include <unordered_map>
#include "AApiHandler.hpp"

namespace http {

  class ApiHandler : public AApiHandler {

  public:
    ApiHandler(const ApiHandler&) = delete;
    ApiHandler& operator=(const ApiHandler&) = delete;

    explicit ApiHandler();

  private:
    void registerCalls();

  };

} // namespace http

namespace direct {

  class ApiHandler : public AApiHandler {

  public:
    ApiHandler(const ApiHandler&) = delete;
    ApiHandler& operator=(const ApiHandler&) = delete;

    explicit ApiHandler();

  private:
    void registerCalls();

  };

} // namespace http


#endif // API_HANDLER_HPP_
