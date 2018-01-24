/*
** SocketInclude.hpp for PSU_2016_zappy in /Users/gmblucas/Desktop/Shared/PSU_2016_zappy/zappy_gui/includes
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Thu Jun 22 21:02:29 2017 Lucas Gambini
** Last update Thu Jun 22 21:04:07 2017 Lucas Gambini
*/

#ifndef SOCKETINCLUDE_HPP
#define SOCKETINCLUDE_HPP

typedef int SOCKET;

#if defined (WIN32)
    #include <winsock2.h>
    typedef int socklen_t;
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <strings.h>

    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close (s)

    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
#endif

#endif /* !SOCKETINCLUDE_HPP */
