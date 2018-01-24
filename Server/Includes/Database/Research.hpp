#ifndef             RESEARCH
#define             RESEARCH


#include            "Database/IObject.hpp"

enum Comparator {
    GREATER,
    LOWER,
    EQUAL,
    NOT_EQUAL,
    GREATER_OR_EQUAL,
    LOWER_OR_EQUAL
};

class               Research {
    std::string _name;
    Comparator _comparator;
    IObject *_value;
public:
    explicit Research(std::string const &name, Comparator comparator, IObject *value);
    std::string const &getName() const;
    Comparator getComparator() const;
    IObject *getValue() const;
};

#else

class Research;

#endif /* !RESEARCH */
