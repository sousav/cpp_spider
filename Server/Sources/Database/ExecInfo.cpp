#include            "Database/ExecInfo.hpp"

ExecInfo::ExecInfo(const std::string& command, const std::string& result) : Bdd("ExecInfo", ToDo::create)
{
    this->addObject("command", new String(command));
    this->addObject("result", new String(result));
}
