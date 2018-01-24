#include                "Database/Float.hpp"

Float::Float(float myFloat)
{
    this->_myFloat = myFloat;
}

Float::Float(std::string const &value)
{
    this->_myFloat = std::stof(value);
}

Float::~Float()
{
}

int Float::getValue() const
{
    return (this->_myFloat);
}

std::string Float::getType() const
{
    return (std::string("Float"));
}

std::string Float::getJSON() const
{
    return (std::to_string(this->_myFloat));
}

IObject *Float::copyObject() const
{
    IObject *tmp = new Float(this->_myFloat);

    return (tmp);
}

bool Float::isEqual(Research object) const
{
    float value;

    if (object.getValue()->getType() == this->getType())
    {
        value = ((Float *)object.getValue())->_myFloat;
        if (object.getComparator() == Comparator::EQUAL && value == this->_myFloat)
            return (true);
        else if (object.getComparator() == Comparator::NOT_EQUAL && value != this->_myFloat)
            return (true);
        else if (object.getComparator() == Comparator::GREATER && value > this->_myFloat)
            return (true);
        else if (object.getComparator() == Comparator::LOWER && value < this->_myFloat)
            return (true);
        else if (object.getComparator() == Comparator::GREATER_OR_EQUAL && value >= this->_myFloat)
            return (true);
        else if (object.getComparator() == Comparator::LOWER_OR_EQUAL && value <= this->_myFloat)
            return (true);
    }
    return (false);
}

std::string Float::getRealJSON(std::string const &name, bool display) const {
    std::string tmp;
    int i = 0;

    tmp += "\"";
    tmp += name;
    tmp += "\" : ";
    tmp += std::to_string(this->_myFloat);
    return (tmp);
}
