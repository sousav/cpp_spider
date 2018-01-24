//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#ifndef DUMP_HPP_
#define DUMP_HPP_

#include "AContent.hpp"

namespace direct {

  class Dump: public AContent {

  public:
    Dump(const std::string &content);
    ~Dump();

    const std::string &getOrigin() const;
    const std::string &getContent() const;

  private:
    void onPropertyFound(const boost::property_tree::ptree::const_iterator &it);

    std::string _origin;
    std::string _content;

  };

}

#endif /*DUMP_HPP_*/
