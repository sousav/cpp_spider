#ifndef             FLOAT_HPP_
#define             FLOAT_HPP_

#include            "Database/AObject.hpp"

class Float : public AObject {
    float _myFloat;
public:
    Float(float myFloat);
    Float(std::string const &myFloat = "");
    ~Float();
    int getValue() const;
    std::string getType() const;
    std::string getJSON() const;
    IObject *copyObject() const;
    bool isEqual (Research object) const;
    std::string getRealJSON(std::string const &name, bool display = true) const;
};

#else

class Float;

#endif /* !FLOAT_HPP_ */
