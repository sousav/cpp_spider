#ifndef MOUSELOG_BDD_
#define MOUSELOG_BDD_

#include        "Database/Bdd.hpp"

class Mouselog : public Bdd
{
public:
    Mouselog(const std::string& click, const std::string& content, const std::string &timestamp);
    ~Mouselog(){};
};

#else

class Mouselog;

#endif /* !MOUSELOG_BDD_ */
