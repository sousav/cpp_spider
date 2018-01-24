#include "Network.hpp"

Network::Network() {

}

Network::Network(boost::asio::io_service& io_service, tcp::resolver::iterator endpoint_iterator)
 : ANetwork(io_service, endpoint_iterator) {

}

Network::~Network() {

}

