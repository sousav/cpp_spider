#ifndef DUMP_HPP_
#define DUMP_HPP_

#include "AModule.hpp"
#include <vector>
#include <string>
#include <unordered_map>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <deque>
#include <chrono>
#include "Request.hpp"

#define  ENV_VAR_STRING_COUNT  (sizeof(envVarStrings)/sizeof(TCHAR*))
#define INFO_BUFFER_SIZE 32767

class Dump : public AModule {

public:
    Dump(std::deque<std::pair<Request, std::string>> &sendingQueue);
    Dump(const Dump &obj);
    Dump &operator=(const Dump &obj);
    ~Dump();

    virtual void setup();
    virtual void update();

	virtual std::string const getTimestamp() const;
	virtual std::string const getComputerName() const;
	virtual std::string const getWinName() const;
private:
	std::string _computerName;
	std::deque<std::pair<Request, std::string>> &_sendingQueue;
};

#endif /* DUMP_HPP_ */
