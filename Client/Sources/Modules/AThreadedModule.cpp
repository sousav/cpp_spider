/*
** AThreadedModule.cpp for Client in /Users/gmblucas/Desktop/Shared/Epitech/cpp_spider/Client/Sources/Modules
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Wed Sep 27 19:40:36 2017 Lucas Gambini
** Last update Sat Sep 30 10:36:45 2017 Lucas Gambini
*/

#include "AThreadedModule.hpp"

AThreadedModule::AThreadedModule() {
    this->_status = RUNNING;
}

AThreadedModule::~AThreadedModule() {

}

std::thread &AThreadedModule::getThread() {
    return this->_thread;
}

void AThreadedModule::pause() {
    this->_status = WAITING;
}

AThreadedModule::Status const AThreadedModule::getStatus() const
{
	return this->_status;
}
