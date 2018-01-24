//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#ifndef ACONTENT_HPP_
#define ACONTENT_HPP_

#include "IContent.hpp"

namespace direct {

  class AContent: public IContent {

  public:
    AContent();
    virtual ~AContent();

    virtual ContentType const &getContentType() const;
    virtual const std::string &getClientID() const;

  protected:
    ContentType _type;
    std::string _clientID;

    void readProperty(boost::property_tree::ptree const& pt);
    virtual void onPropertyFound(const boost::property_tree::ptree::const_iterator &it);

  };

}

#endif /*ACONTENT_HPP_*/
