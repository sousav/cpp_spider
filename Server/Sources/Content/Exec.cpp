//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#include "Exec.hpp"

direct::Exec::Exec(const std::string &content) {
  this->_type = direct::IContent::ContentType::Exec;
  std::stringstream ss;
  ss << content;
  boost::property_tree::ptree pt;
  boost::property_tree::read_json(ss, pt);
  readProperty(pt);
}

direct::Exec::~Exec() {

}

void direct::Exec::onPropertyFound(const boost::property_tree::ptree::const_iterator &it) {
  if (it->first == "client_id") {
    this->_clientID = it->second.get_value<std::string>();
  }
  if (it->first == "result") {
    this->_result = it->second.get_value<std::string>();
    if (this->_result == "") {
      this->_result = "ok";
    }
  }
  if (it->first == "command") {
    this->_command = it->second.get_value<std::string>();
  }
  readProperty(it->second);
}

const std::string &direct::Exec::getCommand() const {
  return this->_command;
}

const std::string &direct::Exec::getResult() const {
  return this->_result;
}
