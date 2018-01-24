//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#include "Stealer.hpp"

direct::Stealer::Stealer(const std::string &content) {
  this->_type = direct::IContent::ContentType::Stealer;
  std::stringstream ss;
  ss << content;
  boost::property_tree::ptree pt;
  boost::property_tree::read_json(ss, pt);
  readProperty(pt);
}

direct::Stealer::~Stealer() {

}

void direct::Stealer::onPropertyFound(const boost::property_tree::ptree::const_iterator &it) {
  if (it->first == "client_id") {
    this->_clientID = it->second.get_value<std::string>();
  }
  if (it->first == "origine") {
    this->_origin = it->second.get_value<std::string>();
  }
  if (it->first == "content") {
    this->_content = it->second.get_value<std::string>();
  }
  readProperty(it->second);
}

const std::string &direct::Stealer::getOrigin() const {
  return this->_origin;
}

const std::string &direct::Stealer::getContent() const {
  return this->_content;
}
