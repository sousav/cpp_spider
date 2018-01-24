/*
** EventReceiver.hpp for PSU_2016_zappy in /Users/gmblucas/Desktop/Shared/PSU_2016_zappy/zappy_gui/includes
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Wed Jun 21 17:46:03 2017 Lucas Gambini
** Last update Wed Jun 21 17:46:17 2017 Lucas Gambini
*/

#ifndef EVENTRECEIVER_HPP
#define EVENTRECEIVER_HPP

#include <queue>
#include <mutex>
#include <string>
#include <sstream>
#include <iostream>

class EventReceiver {
    
public:
    EventReceiver();
    ~EventReceiver();
    
    void addEvent(std::string const &cmd);
    
    void lockBuffer();
    void unlockBuffer();
    
protected:
    std::queue<std::string> _buffer;
    
private:
    std::mutex _mutex;
    
    
};

#endif /* !EVENTRECEIVER_HPP */
