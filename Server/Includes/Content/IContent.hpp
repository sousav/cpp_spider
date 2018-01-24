//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#ifndef ICONTENT_HPP_
#define ICONTENT_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace direct {

  class IContent {

  public: enum ContentType {
    Status,
    Exec,
    Dump,
    Mouse,
    Stealer,
    Keyboard,
    Undefined
  };

  public:
    virtual ~IContent() {}
    static IContent *IContentCreator(const std::string& request);
    virtual ContentType const &getContentType() const = 0;

  protected:
    virtual void readProperty(boost::property_tree::ptree const& pt) = 0;
    virtual void onPropertyFound(const boost::property_tree::ptree::const_iterator &it) = 0;

  };

}

#endif /*ICONTENT_HPP_*/
