/*
** Socket.hpp for PSU_2016_zappy in /Users/gmblucas/Desktop/Shared/PSU_2016_zappy/zappy_gui/includes
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Thu Jun 22 21:04:36 2017 Lucas Gambini
** Last update Thu Jun 22 21:05:19 2017 Lucas Gambini
*/

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <cstdlib>
#include        <string>
#include        "SocketInclude.hpp"

#define MAX_BUFF_SIZE 32

class Socket {

public:
    Socket ();
    virtual ~Socket ();
    Socket(Socket &obj);
    Socket    &operator=(Socket &obj);
    std::string const &getIp() const;
    void write(std::string const &str);
    std::string read();
    void close();
    SOCKET getFd() const;
    void setFd(SOCKET fd);
    bool isStarted() const;
    bool isDetach() const;
    void detach();
    void join();
    void setListener(fd_set *fdset, int &max) const;
    virtual void reciveCommand(std::string const &cmd) = 0;

protected:
    SOCKET _fd;
    std::string _ip;
    bool _started;
    bool _detach;

};

#endif /* !SOCKET_HPP */
