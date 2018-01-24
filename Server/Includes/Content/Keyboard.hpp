//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#ifndef KEYBOARD_HPP_
#define KEYBOARD_HPP_

#include "AContent.hpp"

namespace direct {

  class Keyboard: public AContent {

  public:
    Keyboard(const std::string &content);
    ~Keyboard();

    const std::string &getTimestamp() const;
    const std::string &getContent() const;
    const std::string &getProcessName() const;

  private:
    void onPropertyFound(const boost::property_tree::ptree::const_iterator &it);

    std::string _timestamp;
    std::string _content;
    std::string _processName;

  };

}

#endif /*KEYBOARD_HPP_*/
