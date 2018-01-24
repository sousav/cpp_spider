#ifndef ANETWORK_HPP_
#define ANETWORK_HPP_

#include "EventReceiver.hpp"
#include "Client.hpp"
#include "INetwork.hpp"
#include "Message.hpp"

class ANetwork: public INetwork, private Client, private EventReceiver {

public:
  ANetwork();
  ANetwork(boost::asio::io_service& io_service, tcp::resolver::iterator const &endpoint_iterator);
  virtual ~ANetwork();

  virtual void connect(tcp::resolver::iterator const &endpoint_iterator);
  virtual void disconnect();

  virtual void sendMessage(const direct::Message &msg);

  virtual void setReceive(std::string const &event, std::function<void(boost::property_tree::ptree &)> const &callback);
  virtual void setCallback(const CallbackType &callbackType, std::function<void(const std::string &)> const &callback);

  virtual bool isConnected() const;
  virtual void setClientId(std::string const &id);

protected:
  std::function<void(const std::string &)> _connectCallback;
  std::function<void(const std::string &)> _disconnectCallback;
  std::unordered_map<std::string, std::function<void(boost::property_tree::ptree &)>> _receiveCallback;
  bool _connected;
  std::string _id;
  boost::asio::io_service &_ioService;
  tcp::socket _socket;
  direct::Message _readMsg;
  std::deque<direct::Message> _writeMsg;

private:
  void _readHeader();
  void _readBody();
  void _write();
  void _findEvent(std::string const &response) const;
};

#endif /* ANETWORK_HPP_ */
