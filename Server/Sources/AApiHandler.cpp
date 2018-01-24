//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#include "AApiHandler.hpp"

#include "Status.hpp"
http::AApiHandler::AApiHandler() {
  this->registerCalls();
}

http::Reply http::AApiHandler::resolve(const std::string& request, const std::string &body) {
  if (this->_callMap.find(request) == this->_callMap.end()) {
    return http::Reply::stock_reply(http::Reply::status_type::not_found);
  } else {
    return this->_callMap[request](request, body);
  }
}

void http::AApiHandler::registerCall(const std::string& request, const std::function<Reply(const std::string&, const std::string&)>& functor) {
  this->_callMap[request] = functor;
}

void http::AApiHandler::registerCalls() {

}


direct::AApiHandler::AApiHandler() {
  this->registerCalls();
}

direct::Message direct::AApiHandler::resolve(const std::string& request) {
  std::cout << "received: " << request << std::endl;
  direct::IContent *content = direct::IContent::IContentCreator(request);
  if (this->_callMap.find(content->getContentType()) == this->_callMap.end()) {
    return this->_callMap[direct::IContent::ContentType::Undefined](content);
  } else {
    return this->_callMap[content->getContentType()](content);
  }
}

void direct::AApiHandler::registerCall(const direct::IContent::ContentType& contentType, const std::function<Message(const direct::IContent *)>& functor) {
  this->_callMap[contentType] = functor;
}

void direct::AApiHandler::registerCalls() {
  this->_callMap[direct::IContent::ContentType::Undefined] = [](const direct::IContent* request) {
    return direct::Message("{\"res\": false, \"error\": \"command not found\"}");
  };
}
