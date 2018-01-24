#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include "ANetwork.hpp"

class Network: public ANetwork {

public:
  Network();
  Network(boost::asio::io_service& io_service, tcp::resolver::iterator endpoint_iterator);
  ~Network();

};

#endif /*NETWORK_HPP_*/
