#ifndef INETWORK_HPP_
#define INETWORK_HPP_

#include <boost/asio.hpp>
#include <unordered_map>
#include <functional>
#include "Message.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using boost::asio::ip::tcp;

class INetwork {

public: enum CallbackType {
    Connect,
    Disconnect
};

public:
  virtual ~INetwork() {}

  virtual void connect(tcp::resolver::iterator const &endpoint_iterator) = 0;
  virtual void disconnect() = 0;

  virtual void sendMessage(const direct::Message &msg) = 0;

  virtual void setReceive(std::string const &event, std::function<void(boost::property_tree::ptree &)> const &callback) = 0;
  virtual void setCallback(const CallbackType &callbackType, std::function<void(const std::string &)> const &callback) = 0;

};

#endif /*INETWORK_HPP_*/
