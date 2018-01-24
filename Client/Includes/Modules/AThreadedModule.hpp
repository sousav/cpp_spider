#ifndef ATHREADEDMODULE_HPP_
#define ATHREADEDMODULE_HPP_

#include "IModule.hpp"
#include <thread>

class AThreadedModule : public IModule {

public: enum Status
{
    RUNNING,
    WAITING
};

public:
    AThreadedModule();
    virtual ~AThreadedModule();

    virtual void setup() = 0;
    virtual void update() = 0;

    virtual std::thread &getThread();
    virtual void pause();
	virtual Status const getStatus() const;

protected:
    Status _status;
    std::thread _thread;
	bool _connected;
};

#endif /* ATHREADEDMODULE_HPP_ */
