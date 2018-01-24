//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#ifndef MOUSE_HPP_
#define MOUSE_HPP_

#include "AContent.hpp"

namespace direct {

  class Mouse: public AContent {

  public:
    Mouse(const std::string &content);
    ~Mouse();

    const std::string &getTimestamp() const;
    const std::string &getPosition() const;
    const std::string &getClick() const;

  private:
    void onPropertyFound(const boost::property_tree::ptree::const_iterator &it);

    std::string _timestamp;
    std::string _position;
    std::string _click;

  };

}

#endif /*MOUSE_HPP_*/
