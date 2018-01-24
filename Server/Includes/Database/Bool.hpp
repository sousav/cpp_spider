#ifndef              BOOL_HPP_
#define              BOOL_HPP_

#include            "Database/AObject.hpp"

class Bool : public AObject {
    bool _myBool;
public:
    Bool(bool myBool);
    Bool(std::string const &myBool = "");
    ~Bool();
    int getValue() const;
    void setValue(bool b);
    std::string getType() const;
    std::string getJSON() const;
    IObject *copyObject() const;
    bool isEqual (Research object) const;
    bool getRealValue() const;
    std::string getRealJSON(std::string const &name, bool display = true) const;
};

#else

class Bool;

#endif /* ! BOOL_HPP_ */
