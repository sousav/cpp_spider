#ifndef EXEC_HPP_
#define EXEC_HPP_

#include "AModule.hpp"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <stdio.h>

class Exec : public AModule {

public:
    Exec();
    Exec(const Exec &obj);
    Exec &operator=(const Exec &obj);
    ~Exec();

	std::string const exec(std::string const &);
    virtual void setup();
    virtual void update();

private:

};

#endif /* EXEC_HPP_ */
