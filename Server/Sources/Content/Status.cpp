//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#include "Status.hpp"

direct::Status::Status(const std::string &content) {
  this->_type = direct::IContent::ContentType::Status;
  std::stringstream ss;
  ss << content;
  boost::property_tree::ptree pt;
  boost::property_tree::read_json(ss, pt);
  readProperty(pt);
}

direct::Status::~Status() {

}

void direct::Status::onPropertyFound(const boost::property_tree::ptree::const_iterator &it) {
  if (it->first == "client_id") {
    this->_clientID = it->second.get_value<std::string>();
  }
  if (it->first == "status") {
    this->_status = it->second.get_value<std::string>();
  }
  readProperty(it->second);
}

const std::string &direct::Status::getStatus() const {
  return this->_status;
}
