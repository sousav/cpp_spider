//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#include "AContent.hpp"

direct::AContent::AContent() : _type(direct::IContent::ContentType::Undefined){

}

direct::AContent::~AContent() {

}

direct::IContent::ContentType const &direct::AContent::getContentType() const {
  return this->_type;
}

void direct::AContent::readProperty(boost::property_tree::ptree const& pt) {
    boost::property_tree::ptree::const_iterator end = pt.end();
    for (boost::property_tree::ptree::const_iterator it = pt.begin(); it != end; ++it) {
      onPropertyFound(it);
    }
}

void direct::AContent::onPropertyFound(const boost::property_tree::ptree::const_iterator &it) {
  std::cout << it->first << ": " << it->second.get_value<std::string>() << std::endl;
  readProperty(it->second);
}

const std::string &direct::AContent::getClientID() const {
  return this->_clientID;
}
