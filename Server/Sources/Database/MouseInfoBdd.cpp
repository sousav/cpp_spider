#include            "Database/MouseInfoBdd.hpp"

MouseInfoBdd::MouseInfoBdd(std::string client_id, int timestamp, float x, float y, std::string click) : Bdd("MouseInfoBdd", ToDo::create)
{
    this->addObject("client_id", new String(client_id));
    this->addObject("timestamp", new Int(timestamp));
    this->addObject("x", new Float(x));
    this->addObject("y", new Float(y));
    this->addObject("click", new String(click));
}
