//
//  main.hpp
//  spider_server
//
//  Created by Victor Sousa on 28/09/2017.
//
//

#include "Database/BddEndPoint.hpp"

BddEndPoint::BddEndPoint() {

}

BddEndPoint::~BddEndPoint() {

}


std::vector<IObject *>BddEndPoint::getClientsArray() {
  Bdd *Clients = NULL;
  if ((Clients = (*Bdd::singleton)["Clients"]) == NULL) {
    Clients = new Bdd("Clients", ToDo::create, true);
    Bdd::singleton->addLine(Clients);
    return BddEndPoint::getClientsArray();
  }
  return Clients->find(std::vector<Research>{});
}

Bdd *BddEndPoint::getClientsBdd() {
  Bdd *Clients = NULL;
  if ((Clients = (*Bdd::singleton)["Clients"]) == NULL) {
    Clients = new Bdd("Clients", ToDo::create, true);
    Bdd::singleton->addLine(Clients);
    return BddEndPoint::getClientsBdd();
  }
  return Clients;
}

IObject *BddEndPoint::getClientsByID(const std::string &client_id) {
  Bdd *Clients = BddEndPoint::getClientsBdd();
  std::vector<Research> seekData;
  std::vector<IObject *> results;
  String client_id_string(client_id);
  seekData.push_back(Research("client_id", Comparator::EQUAL, &client_id_string));
  results = Clients->find(seekData);
  if (results.size() == 0) {
    Client *createdClient = new Client(client_id, false);
    Clients->addLine(createdClient);
    return BddEndPoint::getClientsByID(client_id);
  }
  return results[0];
}

std::vector<IObject *> BddEndPoint::getClientsBySeek(const Research &seek) {
  Bdd *Clients = BddEndPoint::getClientsBdd();
  std::vector<Research> seekData;
  std::vector<IObject *> results;
  seekData.push_back(seek);
  results = Clients->find(seekData);
  return results;
}

std::vector<IObject *> BddEndPoint::getClientsBySeeks(const std::vector<Research> &seekData) {
  Bdd *Clients = BddEndPoint::getClientsBdd();
  std::vector<IObject *> results;
  results = Clients->find(seekData);
  return results;
}

std::string BddEndPoint::getClientsJson() {
  boost::property_tree::ptree root;
  std::stringstream ss;
  ss << "{" << BddEndPoint::getClientsBdd()->getRealJSON("");
  std::cout << ss.str() << std::endl;
  boost::property_tree::json_parser::read_json(ss, root);
  std::stringstream ss1;
  boost::property_tree::json_parser::write_json(ss1, root);
  return ss1.str();
}

void BddEndPoint::setIPOfClient(const std::string &ip, const std::string &client_id) {
  Client *client = static_cast<Client *>(BddEndPoint::getClientsByID(client_id));
  String *str_ip = static_cast<String *>((*client)("ip"));
  str_ip->setValue(ip);
}
