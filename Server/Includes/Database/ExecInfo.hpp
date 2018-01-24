#ifndef EXECINFO_BDD_
#define EXECINFO_BDD_

#include        "Database/Bdd.hpp"

class ExecInfo : public Bdd
{
public:
    ExecInfo(const std::string& command, const std::string& result);
    ~ExecInfo(){};

};

#else

class ExecInfo;

#endif /* !EXECINFO_BDD_ */
