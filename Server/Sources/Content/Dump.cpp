//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#include "Dump.hpp"

direct::Dump::Dump(const std::string &content) {
  this->_type = direct::IContent::ContentType::Dump;
  std::stringstream ss;
  ss << content;
  boost::property_tree::ptree pt;
  boost::property_tree::read_json(ss, pt);
  readProperty(pt);
}

direct::Dump::~Dump() {

}

void direct::Dump::onPropertyFound(const boost::property_tree::ptree::const_iterator &it) {
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

const std::string &direct::Dump::getOrigin() const {
  return this->_origin;
}

const std::string &direct::Dump::getContent() const {
  return this->_content;
}
