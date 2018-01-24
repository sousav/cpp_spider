//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <vector>
#include "Header.hpp"

namespace http {

  struct Request
  {
    std::string method;
    std::string uri;
    int http_version_major;
    int http_version_minor;
    std::vector<Header> headers;
  };

} // namespace http

#endif // HTTP_REQUEST_HPP
