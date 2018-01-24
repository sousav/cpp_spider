/*
** EventReceiver.cpp for PSU_2016_zappy in /Users/gmblucas/Desktop/Shared/PSU_2016_zappy/zappy_gui/sources
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Wed Jun 21 17:47:42 2017 Lucas Gambini
** Last update Wed Jun 21 17:47:48 2017 Lucas Gambini
*/

#include "EventReceiver.hpp"

EventReceiver::EventReceiver() {
    
}

EventReceiver::~EventReceiver() {
    
}

void EventReceiver::addEvent(std::string const &cmd) {
    std::stringstream ss(cmd);
    std::string to;
    
    while(std::getline(ss, to, '\n')){
        this->_buffer.push(to + "\n");
    }
}

void EventReceiver::lockBuffer() {
    while (this->_mutex.try_lock() == false);
}

void EventReceiver::unlockBuffer() {
    this->_mutex.unlock();
}
