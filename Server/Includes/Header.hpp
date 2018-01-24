//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#ifndef HTTP_HEADER_HPP
#define HTTP_HEADER_HPP

#include <string>

namespace http {

  struct Header
  {
    std::string name;
    std::string value;
  };

} // namespace http

#endif // HTTP_HEADER_HPP
