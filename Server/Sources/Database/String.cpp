#include                "Database/String.hpp"

String::String(std::string const &myString)
{
    this->_myString = myString;
}

String::~String()
{
}

int String::getValue() const
{
    return (1);
}

void String::setValue(const std::string &str) {
  this->_myString = str;
}

std::string String::getType() const
{
    return (std::string("String"));
}

std::string String::getJSON() const
{
    return ("\"" + this->_myString + "\"");
}

IObject *String::copyObject() const
{
    IObject *tmp = new String(this->_myString);

    return (tmp);
}

bool String::isEqual(Research object) const
{
    std::string value;

    if (object.getValue()->getType() == this->getType())
    {
        value = ((String *)object.getValue())->_myString;
        if (object.getComparator() == Comparator::EQUAL && value == this->_myString)
            return (true);
        else if (object.getComparator() == Comparator::NOT_EQUAL && value != this->_myString)
            return (true);
        else if (object.getComparator() == Comparator::GREATER && value > this->_myString)
            return (true);
        else if (object.getComparator() == Comparator::LOWER && value < this->_myString)
            return (true);
        else if (object.getComparator() == Comparator::GREATER_OR_EQUAL && value >= this->_myString)
            return (true);
        else if (object.getComparator() == Comparator::LOWER_OR_EQUAL && value <= this->_myString)
            return (true);
    }
    return (false);
}

std::string String::getRealJSON(std::string const &name, bool display) const {
    std::string tmp;
    int i = 0;

    tmp += "\"";
    tmp += name;
    tmp += "\" : \"";
    tmp += this->_myString;
    tmp += "\"";
    return (tmp);
}

std::string const &String::getData() const {
  return this->_myString;
}
