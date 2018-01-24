#ifndef CLIENT_BDD_
#define CLIENT_BDD_

#include        "Database/Bdd.hpp"

class Client : public Bdd
{
public:
    Client(std::string client_id = "undefined", bool status = false);
    ~Client(){};

    virtual boost::property_tree::ptree getRealJSON() const;

};

#else

class Client;

#endif /* !CLIENT_BDD_ */
