#ifndef IOBJECT_HPP_
#define IOBJECT_HPP_

#include            <string>
#include <boost/property_tree/ptree.hpp>
#include            "Research.hpp"

enum ToDo {
    load,
    create,
    parse
};

class IObject {
protected:
    virtual std::string getInfoJSON(std::string const &str, std::string const &toFind) const = 0;
    virtual std::size_t getCloseJSON(std::string const &str, std::size_t pos) const = 0;
public:
    virtual ~IObject(){};
    virtual int getValue() const = 0;
    virtual std::string getType() const = 0;
    virtual std::string getJSON() const = 0;
    virtual IObject *copyObject() const = 0;
    virtual bool isEqual(Research object) const = 0;
    virtual std::string getRealJSON(std::string const &name, bool display = true) const = 0;

};

#else

class IObject;

#endif /* !IOBJECT_HPP_ */
