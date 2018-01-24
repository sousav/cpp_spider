//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#ifndef BDDENDPOINT_HPP_
#define BDDENDPOINT_HPP_

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Database/Bdd.hpp"
#include "Database/Client.hpp"

class BddEndPoint {

public:
  BddEndPoint(const BddEndPoint&) = delete;
  BddEndPoint& operator=(const BddEndPoint&) = delete;

  explicit BddEndPoint();
  virtual ~BddEndPoint();

public: static std::vector<IObject *>getClientsArray();
public: static Bdd *getClientsBdd();

public: static IObject *getClientsByID(const std::string &client_id);
public: static std::vector<IObject *> getClientsBySeek(const Research &client_id);
public: static std::vector<IObject *> getClientsBySeeks(const std::vector<Research> &seeks);
public: static void setIPOfClient(const std::string &ip, const std::string &client_id);
public: static std::string getClientsJson();

};

#endif // BDDENDPOINT_HPP_
