//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#include "main.hpp"
#include "Database/BddEndPoint.hpp"

int main(int ac, char* av[]) {
  if (ac != 4) {
      std::cerr << "Usage: spider_server <address> <port> <root_folder>" << std::endl;
      return 1;
  }

  try {

    Bdd Database(std::string(SOURCE_PATH) + "/Database/data.json", ToDo::load);
    Bdd::singleton = &Database;

    http::Server http(av[1], av[2], av[3]);
    http.run();

    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), std::atoi(av[2]) + 1);
    direct::Server socket(endpoint);
    socket.run();

    std::cout << "Enter exit to shutdown both server" << std::endl;
    std::cout << "type in any command you want to send to all client" << std::endl;
    std::string request;
    while (std::getline(std::cin, request)) {
      if (request == "exit") {
        break;
      }
      socket.broadcast(request);
    }

    http.stop();
    socket.stop();

    Database.save(std::string(SOURCE_PATH) + "/Database/data");

  } catch (std::exception& e) {
    std::cerr << "exception: " << e.what() << "\n";
    return main(ac, av);
  }
  return 0;
}
