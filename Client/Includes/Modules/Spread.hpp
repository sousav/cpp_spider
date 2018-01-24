#ifndef SPREAD_HPP_
#define SPREAD_HPP_

#include "AModule.hpp"
#include <shlobj.h>
#include <iostream>
#include <sstream>

class Spread : public AModule {

public:
    Spread();
	Spread(const Spread &obj);
	Spread &operator=(const Spread &obj);
    ~Spread();

    virtual void setup();
    virtual void update();


private:
	std::string _binName;
	std::string _desktop;
};

#endif /* SpREAD_HPP_ */
