#include                "Database/AObject.hpp"

std::string AObject::getInfoJSON(std::string const &str, std::string const &toFind) const
{
    std::size_t foundStart;
    std::size_t foundEnd;

    foundStart = str.find(toFind);
    if (foundStart != std::string::npos)
    {
        foundStart = str.find(":", foundStart + toFind.size());
        if (foundStart != std::string::npos)
        {
            foundStart++;
            while (str[foundStart] == ' ')
                foundStart++;
            if ((foundEnd = this->getCloseJSON(str, foundStart)) == std::string::npos)
                return (std::string(""));
            if (str[foundStart] == '{' || str[foundStart] == '"')
                foundStart++;
            return (str.substr(foundStart, foundEnd - foundStart));
        }
    }
    return (std::string(""));
}

std::size_t AObject::getCloseJSON(std::string const &str, std::size_t pos) const
{
    char c = str[pos];
    int state;

    state = 0;
    pos++;
    while (str[pos])
    {
        if ((c == '"' && str[pos] == c) || (c == '{' && str[pos] == '}' && state == 0) ||
        (c != '{' && c != '"' && (str[pos] == ' ' || str[pos] == ',' || str[pos] == '}')))
            return (pos);
        else if (str[pos] == '}')
            state--;
        else if (str[pos] == '{')
            state++;
        pos++;
    }
    return (std::string::npos);
}

std::string AObject::getRealJSON(std::string const &name, bool display) const
{
    return ("");
}
