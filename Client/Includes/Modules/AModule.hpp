#ifndef AMODULE_HPP_
#define AMODULE_HPP_

#include "IModule.hpp"

class AModule : public IModule {

public:
    AModule();
    virtual ~AModule();

    virtual void setup() = 0;
    virtual void update() = 0;

};

#endif /* AMODULE_HPP_ */
