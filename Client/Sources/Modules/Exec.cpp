#include "Exec.hpp"

Exec::Exec() {
}

Exec::~Exec() {
}

Exec &Exec::operator=(const Exec &obj) {
    return (*this);
}

Exec::Exec(const Exec &obj) {

}

void Exec::setup() {
	
}

void Exec::update() {

}

std::string const Exec::exec(std::string const &cmd) {
	std::array<char, 128> buffer;
	std::string result;
	std::shared_ptr<FILE> pipe(_popen(cmd.c_str(), "r"), _pclose);
	if (!pipe)
		return "execution failed.";
	while (!feof(pipe.get())) {
		if (fgets(buffer.data(), 128, pipe.get()) != NULL)
			result += buffer.data();
	}
	return result;
}