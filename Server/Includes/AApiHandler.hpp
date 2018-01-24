//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#ifndef AAPI_HANDLER_HPP_
#define AAPI_HANDLER_HPP_

#include <string>
#include <iostream>
#include <unordered_map>
#include "IContent.hpp"
#include "Reply.hpp"
#include "Message.hpp"

namespace http {

  class AApiHandler {

  public:
    AApiHandler(const AApiHandler&) = delete;
    AApiHandler& operator=(const AApiHandler&) = delete;

    explicit AApiHandler();

    virtual void registerCall(const std::string& request, const std::function<Reply(const std::string&, const std::string&)>&functor);
    virtual Reply resolve(const std::string& request, const std::string &body);

  private:
    void registerCalls();

  protected:
    std::unordered_map<std::string, std::function<Reply(const std::string&, const std::string&)>> _callMap;

  };

} // namespace http

namespace direct {

  class AApiHandler {

  public:
    AApiHandler(const AApiHandler&) = delete;
    AApiHandler& operator=(const AApiHandler&) = delete;

    explicit AApiHandler();

    virtual void registerCall(const IContent::ContentType& contentType, const std::function<Message(const IContent *)>&functor);
    virtual Message resolve(const std::string& request);

  private:
    void registerCalls();

  protected:
    std::unordered_map<IContent::ContentType, std::function<Message(const IContent*)>, std::hash<int>> _callMap;

  };

} // namespace direct

#endif // AAPI_HANDLER_HPP_
