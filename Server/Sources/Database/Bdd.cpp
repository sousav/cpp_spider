//
// Bdd.cpp for Bdd in /Users/leandr_g/Documents/Shared folder/IndieStudio/server/src/
//
// Made by Gaëtan Léandre
// Login   <gaetan.leandre@epitech.eu>
//
// Started on  Wed May 24 13:00:34 2017 Gaëtan Léandre
// Last update Wed Jun  7 11:57:16 2017 Gaëtan Léandre
//

#include                "Database/Bdd.hpp"

Bdd *Bdd::singleton;

Bdd::Bdd(std::string const &file, ToDo todo, bool isArray)
{
    this->_lineIndex = 0;
    this->_title = file;
    std::string json;

    if (todo == ToDo::parse)
        this->parseJSON(file);
    else if (todo == ToDo::load)
    {
        std::ifstream myFile(file);

        if (!myFile.is_open())
        {
            this->addObject("isArray", new Bool(isArray));
            return;
        }
        getline(myFile, json, '\0');
        this->parseJSON(json);
    }
    if (this->_items.find("isArray") == this->_items.end())
        this->addObject("isArray", new Bool(isArray));
}

Bdd::~Bdd()
{
    for (auto x : this->_items)
    {
        delete x.second;
    }
}

Bdd::Bdd(const Bdd &obj)
{
    this->_title = obj._title;
    this->_items = obj._items;
}

Bdd     &Bdd::operator=(const Bdd &obj)
{
    this->_title = obj._title;
    this->_items = obj._items;
    return (*this);
}

IObject    *Bdd::operator()(std::string const &pos) const
{
    if (this->_items.find(pos) != this->_items.end())
        return (this->_items.find(pos)->second);
    return (NULL);
}

IObject    *Bdd::operator()(int pos) const
{
    if (this->_items.find(std::to_string(pos)) != this->_items.end())
        return (this->_items.find(std::to_string(pos))->second);
    return (NULL);
}

Bdd *     Bdd::operator[](std::string const &name)
{
    for (auto x : this->_items)
    {
        if (x.second->getType() == "Bdd" && ((Bdd *)x.second)->getTitle() == name)
            return ((Bdd *)x.second);
    }
    return (NULL);
}

std::string const &Bdd::getTitle() const
{
    return (this->_title);
}

void Bdd::setTitle(std::string const &title)
{
    this->_title = title;
}

void Bdd::addObject(std::string const &name, IObject *object)
{
    this->_items[name] = object;
}

void Bdd::deleteObject(std::string const &name)
{
    if (this->_items.find(name) != this->_items.end())
        this->_items.erase(name);
}

int Bdd::getValue() const
{
    return (-1);
}

std::string Bdd::getType() const
{
    return ("Bdd");
}

std::string Bdd::getJSON() const
{
    std::string result;
    int i;

    i = 0;
    result += "{\"";
    result += this->_title;
    result += "\" : ";
    for (auto x: this->_items)
    {
        if (i != 0)
            result += ", ";
        result += "{type : ";
        result += x.second->getType();
        result += ", name : \"";
        result += x.first;
        result += "\", value : ";
        result += x.second->getJSON();
        result += "}";
        i++;
    }
    result += "}";
    return (result);
}

bool Bdd::empty() const
{
    if (this->_items.size() > 0)
        return (false);
    return (true);
}

IObject *Bdd::copyObject() const
{
    Bdd *tmp = new Bdd(this->_title, ToDo::create);

    for (auto &x: this->_items)
    {
        if (x.second != NULL)
            tmp->addObject(x.first, x.second->copyObject());
        else
            tmp->addObject(x.first, NULL);
    }
    return (tmp);
}

std::string Bdd::getTitleJSON(std::string const &str) const
{
    std::size_t foundStart;
    std::size_t foundEnd;
    std::string phrase;
    std::string tmp;

    foundStart = str.find("\"");
    if (foundStart != std::string::npos)
        foundEnd = str.find("\"", foundStart + 1);
    if (foundStart != std::string::npos && foundEnd != std::string::npos)
        phrase = str.substr(foundStart + 1, foundEnd - foundStart - 1);
    else
        phrase = std::string("");
    return (phrase);
}

std::string Bdd::getObjectJSON(std::string &str) const
{
    std::size_t foundStart;
    std::string phrase("");
    std::string tmp;
    int pos = 0;
    int i = 0;
    bool tild = false;

    foundStart = str.find("{");
    if (foundStart != std::string::npos)
    {
        for (i = foundStart; i < str.size(); i++)
        {
            if (str[i] == '{' && tild == false)
                pos++;
            else if (str[i] == '}' && tild == false)
                pos--;
            else if (str[i] == '\"')
                tild = !tild;
            if (pos == 0)
                break;
        }
        if (pos == 0)
        {
            phrase = str.substr(foundStart, i - foundStart + 1);
            tmp = str.substr(0, foundStart);
            tmp += str.substr(i + 1, str.size() - i);
            str = tmp;
        }
    }
    return (phrase);
}

void Bdd::parseJSON(std::string const &str)
{
    std::string phrase;
    std::string tmp;
    std::string type;
    std::size_t foundStart;
    std::size_t foundEnd;
    std::size_t testEnd;


    foundStart = str.find("{");
    foundEnd = str.find_last_of("}");
    if (foundStart != std::string::npos && foundEnd != std::string::npos)
    {
        phrase = str.substr(foundStart + 1, foundEnd - foundStart - 1);
        this->_title = getTitleJSON(phrase);
        foundStart = phrase.find("{");
        foundEnd = phrase.find_last_of("}");
        if (foundStart != std::string::npos && foundEnd != std::string::npos)
        {
            phrase = phrase.substr(foundStart, foundEnd - foundStart + 1);
            while ((tmp = getObjectJSON(phrase)).size() != 0)
            {
                type = this->getInfoJSON(tmp, "type");
                if (type == "Int")
                    this->addObject(this->getInfoJSON(tmp, "name"), new Int(this->getInfoJSON(tmp, "value")));
                else if (type == "Bdd")
                    this->addObject(this->getInfoJSON(tmp, "name"), new Bdd("{" + this->getInfoJSON(tmp, "value") + "}", ToDo::parse, this->getInfoJSON(tmp, "array") == "true" ? true : false));
                else if (type == "String")
                    this->addObject(this->getInfoJSON(tmp, "name"), new String(this->getInfoJSON(tmp, "value")));
                else if (type == "Float")
                    this->addObject(this->getInfoJSON(tmp, "name"), new String(this->getInfoJSON(tmp, "value")));
                else if (type == "Bool")
                    this->addObject(this->getInfoJSON(tmp, "name"), new Bool(this->getInfoJSON(tmp, "value")));
                else
                    this->_lineIndex--;
                this->_lineIndex++;
            }
        }
    }
}

void Bdd::save(std::string const &fileName)
{
    std::ofstream myfile(fileName + std::string(".json"));

    if (myfile.is_open())
    {
       myfile << this->getJSON();
       myfile.close();
    }
    else
        std::cerr << "Unable to open file" << std::endl;
}

int Bdd::addLine(IObject *tmp)
{
    this->addObject(std::to_string(this->_lineIndex), tmp);
    this->_lineIndex++;
    return (this->_lineIndex - 1);
}

bool Bdd::isEqual(Research object) const
{
    if (object.getValue()->getType() == this->getType() && ((Bdd *)object.getValue())->getTitle() == this->getTitle())
    {
        if (object.getComparator() == Comparator::EQUAL)
            return (true);
    }
    else if (object.getComparator() == Comparator::NOT_EQUAL)
        return (true);
    return (false);
}

bool Bdd::contain(std::vector<Research> research) const
{
    bool test;

    for (auto y: research)
    {
        test = false;
        for (auto x: this->_items)
        {
            if (y.getName() == x.first && x.second->isEqual(y))
            {
                test = true;
                break;
            }
        }
        if (test == false)
            return (false);
    }
    return (true);
}


std::vector<IObject *> Bdd::find(std::vector<Research> research) const
{
    std::vector<IObject *> result;
    std::vector<IObject *> tmp;

    for (auto x: this->_items)
    {
        if (x.second->getType() == "Bdd" && ((Bdd *)x.second)->contain(research))
        {
            result.push_back(x.second);
        }
    }
    return (result);
}

void Bdd::lock() {
  this->_mtx.lock();
}

void Bdd::unlock() {
  this->_mtx.unlock();
}

std::string Bdd::getRealJSON(std::string const &name, bool display) const {
    std::string tmp;
    int i = 0;
    int j = 0;
    std::vector<std::string> passed;

    if (display == true)
    {
        tmp += "\"";
        tmp += this->_title;
        tmp += "\" :";
    }
    else
        tmp += "{";
    for (auto x: this->_items)
    {
        if (x.first != "isArray")
        {
             if (x.second->getType() == "Bdd" && std::find(passed.begin(), passed.end(), ((Bdd *)x.second)->getTitle()) == passed.end())
            {
                if (i != 0)
                    tmp += ", ";
                if (!this->isArray())
                {
                    tmp += "\"";
                    tmp += ((Bdd *)x.second)->getTitle();
                    tmp += "\" : ";
                }
                tmp += "\[";
                j = 0;
                for (auto y: this->_items)
                {
                    if (y.second->getType() == "Bdd" && ((Bdd *)x.second)->getTitle() == ((Bdd *)y.second)->getTitle())
                    {
                        if (j != 0)
                            tmp += ", ";
                        tmp += y.second->getRealJSON(y.first, false);
                        j++;
                    }
                }
                    tmp += "]";
                passed.push_back(((Bdd *)x.second)->getTitle());
                i++;
            }
            else if (x.second->getType() != "Bdd")
            {
                if (i != 0)
                    tmp += ", ";
                tmp += x.second->getRealJSON(x.first, true);
                i++;
            }
        }
    }
    if (this->_items.size() == 1)
        tmp += " []";
    tmp += "}";
    return (tmp);
}

bool Bdd::isArray() const
{
    if (this->_items.find("isArray") != this->_items.end())
        return (((Bool *)(this->_items.find("isArray")->second))->getRealValue());
    return (false);
}

void Bdd::setArray(bool value)
{
    if (this->_items.find("isArray") != this->_items.end())
        ((Bool *)(this->_items.find("isArray")->second))->setValue(value);
    else
        this->addObject("isArray", new Bool(value));
}
