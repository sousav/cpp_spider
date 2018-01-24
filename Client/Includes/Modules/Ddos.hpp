#ifndef DDOS_HPP_
#define DDOS_HPP_

#include "AThreadedModule.hpp"

class Ddos : public AThreadedModule {

public:
	Ddos();
	Ddos(const Ddos &obj);
	Ddos &operator=(const Ddos &obj);
    ~Ddos();

    virtual void setup();
    virtual void update();
	virtual void start(std::string const &ip, int port, int duration);

private:
	SOCKET _sock;
	SOCKADDR_IN _sin;
	int _duration;

};

#endif /* DDOS_HPP_ */
