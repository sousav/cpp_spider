#ifndef DUMPINFO_BDD_
#define DUMPINFO_BDD_

#include        "Database/Bdd.hpp"

class DumpInfo : public Bdd
{
public:
    DumpInfo(const std::string& origin, const std::string& content);
    ~DumpInfo(){};

};

#else

class DumpInfo;

#endif /* !DUMPINFO_BDD_ */
