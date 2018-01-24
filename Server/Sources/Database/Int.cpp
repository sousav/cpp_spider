#include                "Database/Int.hpp"

Int::Int(int myInt)
{
    this->_myInt = myInt;
}

Int::Int(std::string const &value)
{
    this->_myInt = std::stoi(value);
}

Int::~Int()
{
}

int Int::getValue() const
{
    return (this->_myInt);
}

std::string Int::getType() const
{
    return (std::string("Int"));
}

std::string Int::getJSON() const
{
    return (std::to_string(this->_myInt));
}

IObject *Int::copyObject() const
{
    IObject *tmp = new Int(this->_myInt);

    return (tmp);
}

bool Int::isEqual(Research object) const
{
    if (object.getValue()->getType() == this->getType())
    {
        if (object.getComparator() == Comparator::EQUAL && object.getValue()->getValue() == this->getValue())
            return (true);
        else if (object.getComparator() == Comparator::NOT_EQUAL && object.getValue()->getValue() != this->getValue())
            return (true);
        else if (object.getComparator() == Comparator::GREATER && object.getValue()->getValue() > this->getValue())
            return (true);
        else if (object.getComparator() == Comparator::LOWER && object.getValue()->getValue() < this->getValue())
            return (true);
        else if (object.getComparator() == Comparator::GREATER_OR_EQUAL && object.getValue()->getValue() >= this->getValue())
            return (true);
        else if (object.getComparator() == Comparator::LOWER_OR_EQUAL && object.getValue()->getValue() <= this->getValue())
            return (true);
    }
    return (false);
}

std::string Int::getRealJSON(std::string const &name, bool display) const {
    std::string tmp;
    int i = 0;

    tmp += "\"";
    tmp += name;
    tmp += "\" : ";
    tmp += std::to_string(this->_myInt);
    return (tmp);
}
