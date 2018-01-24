#ifndef AOBJECT_HHP_
#define AOBJECT_HHP_

#include            "Database/IObject.hpp"

class AObject : public IObject
{
protected:
    virtual std::string getInfoJSON(std::string const &str, std::string const &toFind) const;
    virtual std::size_t getCloseJSON(std::string const &str, std::size_t pos) const;
public:
    virtual ~AObject(){};
    virtual int getValue() const = 0;
    virtual std::string getType() const = 0;
    virtual std::string getJSON() const = 0;
    virtual IObject *copyObject() const = 0;
    virtual bool isEqual(Research object) const = 0;
    virtual std::string getRealJSON(std::string const &name, bool display = true) const;
};

#else

class AObject;

#endif /* !AOBJECT_HHP_ */
