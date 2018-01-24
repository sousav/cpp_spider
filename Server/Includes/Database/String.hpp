#ifndef             STRING_HPP_
#define             STRING_HPP_

#include            "Database/AObject.hpp"

class String : public AObject {
    std::string _myString;
public:
    String(std::string const &myString = "");
    ~String();
    int getValue() const;
    void setValue(const std::string &str);
    std::string getType() const;
    std::string getJSON() const;
    IObject *copyObject() const;
    bool isEqual (Research object) const;
    std::string getRealJSON(std::string const &name, bool display = true) const;
    std::string const &getData() const;
};

#else

class String;

#endif /* !STRING_HPP_ */
