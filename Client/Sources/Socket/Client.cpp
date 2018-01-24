/*
** Client.cpp for PSU_2016_zappy in /Users/gmblucas/Desktop/Shared/PSU_2016_zappy/zappy_gui/sources
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Thu Jun 22 20:23:59 2017 Lucas Gambini
** Last update Sat Sep 30 00:35:19 2017 Lucas Gambini
*/

#include "Client.hpp"

Client::Client() {

}

Client::~Client() {

}

void Client::init(std::string const &ip, int port, EventReceiver *bridge) {
    //this->_socket.init(ip, port, bridge);
    //this->_socket.launchLoop();
    (void)ip;
    (void)port;
    (void)bridge;
}

void Client::stop() {
    //this->_socket.stop();
}

void Client::write(std::string const &cmd) {
    //this->_socket.write(cmd);
    (void)cmd;
}
