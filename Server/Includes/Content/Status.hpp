//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#ifndef STATUS_HPP_
#define STATUS_HPP_

#include "AContent.hpp"

namespace direct {

  class Status: public AContent {

  public:
    Status(const std::string &content);
    ~Status();

    const std::string &getStatus() const;

  private:
    void onPropertyFound(const boost::property_tree::ptree::const_iterator &it);

    std::string _status;

  };

}

#endif /*STATUS_HPP_*/
