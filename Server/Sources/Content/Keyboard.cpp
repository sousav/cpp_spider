//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#include "Keyboard.hpp"

direct::Keyboard::Keyboard(const std::string &content) {
  this->_type = direct::IContent::ContentType::Keyboard;
  std::stringstream ss;
  ss << content;
  boost::property_tree::ptree pt;
  boost::property_tree::read_json(ss, pt);
  readProperty(pt);
}

direct::Keyboard::~Keyboard() {

}

void direct::Keyboard::onPropertyFound(const boost::property_tree::ptree::const_iterator &it) {
  if (it->first == "client_id") {
    this->_clientID = it->second.get_value<std::string>();
  }
  if (it->first == "timestamp") {
    this->_timestamp = it->second.get_value<std::string>();
  }
  if (it->first == "content") {
    this->_content = it->second.get_value<std::string>();
  }
  if (it->first == "process_name") {
    this->_processName = it->second.get_value<std::string>();
  }
  readProperty(it->second);
}

const std::string &direct::Keyboard::getTimestamp() const {
  return this->_timestamp;
}

const std::string &direct::Keyboard::getContent() const {
  return this->_content;
}

const std::string &direct::Keyboard::getProcessName() const {
  return this->_processName;
}
