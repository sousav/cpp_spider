#ifndef KEYLOG_BDD_
#define KEYLOG_BDD_

#include        "Database/Bdd.hpp"

class Keylog : public Bdd
{
public:
    Keylog(const std::string& process_name, const std::string& content, const std::string &timestamp);
    ~Keylog(){};
};

#else

class Keylog;

#endif /* !KEYLOG_BDD_ */
