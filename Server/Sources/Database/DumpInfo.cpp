#include            "Database/DumpInfo.hpp"

DumpInfo::DumpInfo(const std::string& origin, const std::string& content) : Bdd("DumpInfo", ToDo::create)
{
    this->addObject("origin", new String(origin));
    this->addObject("content", new String(content));
}
