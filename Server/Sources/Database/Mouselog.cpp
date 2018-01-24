#include            "Database/Mouselog.hpp"

Mouselog::Mouselog(const std::string& click, const std::string& content, const std::string &timestamp) : Bdd("Mouselog", ToDo::create)
{
    this->addObject("click", new String(click));
    this->addObject("content", new String(content));
    this->addObject("timestamp", new String(timestamp));
}
