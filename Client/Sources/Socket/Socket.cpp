/*
** Socket.cpp for PSU_2016_zappy in /Users/gmblucas/Desktop/Shared/PSU_2016_zappy/zappy_gui/sources
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Thu Jun 22 21:09:03 2017 Lucas Gambini
** Last update Fri Sep 29 23:54:10 2017 Lucas Gambini
*/
//
// #include "Socket.hpp"
//
// Socket::Socket()
// {
//     this->_fd = -1;
//     this->_ip = "";
//     this->_started = false;
//     this->_detach = false;
// }
//
// Socket::~Socket()
// {
//     if (this->_started == true && this->_detach == false)
//         ::close(this->_fd);
// }
//
// Socket::Socket(Socket &obj)
// {
//     this->_fd = obj._fd;
//     this->_ip = obj._ip;
//     this->_started = obj._started;
//     this->_detach = false;
//     obj._detach = true;
// }
//
// Socket &Socket::operator=(Socket &obj)
// {
//     this->_fd = obj._fd;
//     this->_ip = obj._ip;
//     this->_started = obj._started;
//     this->_detach = false;
//     obj._detach = true;
//     return (*this);
// }
//
// std::string const &Socket::getIp() const
// {
//     return (this->_ip);
// }
//
// void Socket::write(std::string const &str)
// {
//     if (this->_started == true)
//         ::write(this->_fd, str.c_str(), str.size() > MAX_BUFF_SIZE - 1 ? MAX_BUFF_SIZE - 1 : str.size());
// }
//
// static int      my_strlen(char *str)
// {
//     int           i;
//
//     i = 0;
//     while (*str != 0)
//     {
//         i++;
//         str++;
//     }
//     return (i);
// }
//
// static char     *my_strncpy(char *dest, char const *src, int n)
// {
//     int           i;
//
//     i = 0;
//     while (src[i] != '\0' && i < n)
//     {
//         dest[i] = src[i];
//         i++;
//     }
//     if (n < i)
//         dest[i] = '\0';
//     return (dest);
// }
//
// static char     *add_to_line(char *line, int treat, char *buff, int *start)
// {
//     char          *newlen;
//     int           oldlen;
//
//     if (line != 0)
//         oldlen = my_strlen(line);
//     else
//         oldlen = 0;
//     newlen = (char *)malloc((oldlen + treat + 1) * sizeof(*newlen));
//     if (line != 0)
//         my_strncpy(newlen, line, oldlen);
//     else
//         my_strncpy(newlen, std::string("").data(), oldlen);
//     newlen[oldlen + treat] = 0;
//     my_strncpy(newlen + oldlen, buff + *start, treat);
//     if (line)
//         free(line);
//     *start = *start + (treat + 1);
//     return (newlen);
// }
//
// char            *get_next_line(const int fd)
// {
//     static char   buff[MAX_BUFF_SIZE];
//     static int    nbinbuff = 0;
//     static int    start;
//     int           treat;
//     char          *line;
//
//     line = 0;
//     treat = 0;
//     while (1 == 1)
//     {
//         if (nbinbuff <= start)
//         {
//             start = 0;
//             if (!(nbinbuff = read(fd, buff, MAX_BUFF_SIZE)))
//                 return (line);
//             if (nbinbuff == -1)
//                 return (NULL);
//             treat = 0;
//         }
//         if (buff[start + treat] == '\n')
//             return (line = add_to_line(line, treat, buff, &start));
//         if (start + treat == nbinbuff - 1)
//             line = add_to_line(line, treat + 1, buff, &start);
//         treat = treat + 1;
//     }
// }
//
// std::string Socket::read()
// {
//     char *buffer = NULL;
//
//     if (this->_started == true) {
//         buffer = get_next_line(this->_fd);
//     }
//     if (buffer != NULL)
//         return (std::string(buffer));
//     return (std::string("-"));
// }
//
// SOCKET Socket::getFd() const
// {
//     return (this->_fd);
// }
//
// void Socket::setFd(SOCKET fd)
// {
//     if (this->_started == true && this->_detach == false)
//         ::close(this->_fd);
//     this->_fd = fd;
//     this->_started = true;
//     this->_detach = false;
// }
//
// bool Socket::isStarted() const
// {
//     return (this->_started);
// }
//
// bool Socket::isDetach() const
// {
//     return (this->_detach);
// }
//
// void Socket::detach()
// {
//     this->_detach = true;
// }
//
// void Socket::join()
// {
//     this->_detach = false;
// }
//
// void Socket::setListener(fd_set *fdset, int &max) const
// {
//     if (this->_started == true)
//     {
//         FD_SET(this->_fd, fdset);
//         max = this->_fd > max ? this->_fd : max;
//     }
// }
