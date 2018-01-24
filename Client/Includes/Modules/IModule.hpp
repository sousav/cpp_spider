#ifndef IMODULE_HPP_
#define IMODULE_HPP_

#include <iostream>
#include <Windows.h>

class IModule {

public:
    virtual ~IModule() {};

    virtual void setup() = 0;
    virtual void update() = 0;

};

#endif /* IMODULE_HPP_ */
