#ifndef MOUSE_HPP_
#define MOUSE_HPP_

#include "AThreadedModule.hpp"
#include <utility>
#include <deque>
#include <vector>
#include "Request.hpp"

class Mouse : public AThreadedModule {

public:
    Mouse(std::deque<std::pair<Request, std::string>> &sendingQueue);
    Mouse(const Mouse &obj);
    Mouse &operator=(const Mouse &obj);
    ~Mouse();

    virtual void update();
    virtual void setup();

private:
	std::deque<std::pair<Request, std::string>> &_sendingQueue;
};

#endif /* MOUSE_HPP_ */
