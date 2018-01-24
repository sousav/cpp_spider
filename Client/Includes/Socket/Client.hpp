/*
** Client.hpp for PSU_2016_zappy in /Users/gmblucas/Desktop/Shared/PSU_2016_zappy/zappy_gui/includes
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Thu Jun 22 20:24:07 2017 Lucas Gambini
** Last update Fri Sep 29 23:52:17 2017 Lucas Gambini
*/

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <memory>
#include "EventReceiver.hpp"

class Client {

public:
    Client();
    ~Client();

    void init(std::string const &ip, int port, EventReceiver *bridge);
    void stop();

    void write(std::string const &cmd);

protected:
    // ClientSocket _socket;

};

#endif /* !CLIENT_HPP */
