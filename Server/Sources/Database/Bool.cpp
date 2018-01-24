#include                    "Database/Bool.hpp"

Bool::Bool(bool myBool)
{
    this->_myBool = myBool;
}

Bool::Bool(std::string const &value)
{
    if (value == "true")
        this->_myBool = true;
    else
        this->_myBool = false;
}

Bool::~Bool()
{
}

bool Bool::getRealValue() const
{
    return (this->_myBool);
}

int Bool::getValue() const
{
    return (0);
}

void Bool::setValue(bool b) {
  this->_myBool = b;
}

std::string Bool::getType() const
{
    return (std::string("Bool"));
}

std::string Bool::getJSON() const
{
    return (this->_myBool == true ? "true" : "false");
}

IObject *Bool::copyObject() const
{
    IObject *tmp = new Bool(this->_myBool);

    return (tmp);
}

bool Bool::isEqual(Research object) const
{
    bool value;

    if (object.getValue()->getType() == this->getType())
    {
        value = ((Bool *)object.getValue())->_myBool;
        if (object.getComparator() == Comparator::EQUAL && value == this->_myBool)
            return (true);
        else if (object.getComparator() == Comparator::NOT_EQUAL && value != this->_myBool)
            return (true);
        else if (object.getComparator() == Comparator::GREATER && value > this->_myBool)
            return (true);
        else if (object.getComparator() == Comparator::LOWER && value < this->_myBool)
            return (true);
        else if (object.getComparator() == Comparator::GREATER_OR_EQUAL && value >= this->_myBool)
            return (true);
        else if (object.getComparator() == Comparator::LOWER_OR_EQUAL && value <= this->_myBool)
            return (true);
    }
    return (false);
}

std::string Bool::getRealJSON(std::string const &name, bool display) const {
    std::string tmp;
    int i = 0;

    tmp += "\"";
    tmp += name;
    tmp += "\" : ";
    tmp += (this->_myBool == true ? "true" : "false");
    return (tmp);
}
