#ifndef             INT_HHP_
#define             INT_HHP_

#include            "Database/AObject.hpp"

class Int : public AObject {
    int _myInt;
public:
    Int(int myInt = 0);
    Int(std::string const &value);
    ~Int();
    int getValue() const;
    std::string getType() const;
    std::string getJSON() const;
    IObject *copyObject() const;
    bool isEqual (Research object) const;
    std::string getRealJSON(std::string const &name, bool display = true) const;
};

#else

class Int;

#endif /* !INT_HHP_ */
