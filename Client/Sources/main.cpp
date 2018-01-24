#include <iostream>
#include "SpiderClient_Config.h"
#include "Spider.hpp"
#include <windows.h>
#include <shellapi.h>

#if !(_DEBUG)
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
#else
int main()
#endif
{
	try
	{

		std::cout << "Running spider_client." << std::endl << "Build " << BUILD_TYPE << ", Revision " << VERSION_MAJOR << std::endl;

		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);
		auto endpoint_iterator = resolver.resolve({ "93.9.51.53", "3001" });

		Spider spider(io_service, endpoint_iterator);

		spider.start(io_service);
		spider.initModules();
		std::thread t([&io_service]() { io_service.run(); });
		spider.mainLoop();

		spider.stop();
		t.join();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
