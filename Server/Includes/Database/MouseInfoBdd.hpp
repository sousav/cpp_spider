#ifndef MOUSE_INFO_BDD_
#define MOUSE_INFO_BDD_

#include        "Database/Bdd.hpp"

class MouseInfoBdd : public Bdd
{
public:
    MouseInfoBdd(std::string client_id = "", int timestamp = 0, float x = 0, float y = 0, std::string click = "");
    ~MouseInfoBdd(){};
};

#else

class MouseInfoBdd;

#endif /* !MOUSE_INFO_BDD_ */
