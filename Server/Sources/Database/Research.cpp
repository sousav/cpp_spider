#include                "Database/Research.hpp"

Research::Research(std::string const &name, Comparator comparator, IObject *value)
{
    this->_name = name;
    this->_comparator = comparator;
    this->_value = value;
}

std::string const &Research::getName() const
{
    return (this->_name);
}

Comparator Research::getComparator() const
{
    return (this->_comparator);
}

IObject *Research::getValue() const
{
    return (this->_value);
}
