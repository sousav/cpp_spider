//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#include "Mouse.hpp"

direct::Mouse::Mouse(const std::string &content) {
  this->_type = direct::IContent::ContentType::Mouse;
  std::stringstream ss;
  ss << content;
  boost::property_tree::ptree pt;
  boost::property_tree::read_json(ss, pt);
  readProperty(pt);
}

direct::Mouse::~Mouse() {

}

void direct::Mouse::onPropertyFound(const boost::property_tree::ptree::const_iterator &it) {
  if (it->first == "client_id") {
    this->_clientID = it->second.get_value<std::string>();
  }
  if (it->first == "timestamp") {
    this->_timestamp = it->second.get_value<std::string>();
  }
  if (it->first == "mouvements") {
    this->_position = it->second.get_value<std::string>();
  }
  if (it->first == "click") {
    this->_click = it->second.get_value<std::string>();
  }
  readProperty(it->second);
}

const std::string &direct::Mouse::getTimestamp() const {
  return this->_timestamp;
}

const std::string &direct::Mouse::getPosition() const {
  return this->_position;
}

const std::string &direct::Mouse::getClick() const {
  return this->_click;
}
