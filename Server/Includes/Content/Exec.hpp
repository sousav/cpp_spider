//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#ifndef EXEC_HPP_
#define EXEC_HPP_

#include "AContent.hpp"

namespace direct {

  class Exec: public AContent {

  public:
    Exec(const std::string &content);
    ~Exec();

    const std::string &getResult() const;
    const std::string &getCommand() const;

  private:
    void onPropertyFound(const boost::property_tree::ptree::const_iterator &it);

    std::string _result;
    std::string _command;

  };

}

#endif /*EXEC_HPP_*/
