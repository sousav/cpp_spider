//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#ifndef HTTP_REQUEST_HANDLER_HPP
#define HTTP_REQUEST_HANDLER_HPP

#include <string>
#include <iostream>

#include "ApiHandler.hpp"

namespace http {

  struct Reply;
  struct Request;

  class RequestHandler {

  public:
    RequestHandler(const RequestHandler&) = delete;
    RequestHandler& operator=(const RequestHandler&) = delete;

    explicit RequestHandler(const std::string& doc_root);
    void handle_request(const Request& req, Reply& rep, const std::string &body);

  private:
    std::string _doc_root;
    ApiHandler _apiHandler;

    static bool url_decode(const std::string& in, std::string& out);

  };

} // namespace http

#endif // HTTP_REQUEST_HANDLER_HPP
