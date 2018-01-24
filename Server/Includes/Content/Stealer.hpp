//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#ifndef STEALER_HPP_
#define STEALER_HPP_

#include "AContent.hpp"

namespace direct {

  class Stealer: public AContent {

  public:
    Stealer(const std::string &content);
    ~Stealer();

    const std::string &getOrigin() const;
    const std::string &getContent() const;

  private:
    void onPropertyFound(const boost::property_tree::ptree::const_iterator &it);

    std::string _origin;
    std::string _content;

  };

}

#endif /*STEALER_HPP_*/
