//
// Bdd.hh for Bdd in /Users/leandr_g/Documents/Shared folder/IndieStudio/server/inc/
//
// Made by Gaëtan Léandre
// Login   <gaetan.leandre@epitech.eu>
//
// Started on  Wed May 24 12:45:26 2017 Gaëtan Léandre
// Last update Wed Jun  7 11:57:53 2017 Gaëtan Léandre
//

#ifndef              Bdd_HHP_
#define             Bdd_HHP_

#include            <string>
#include            <mutex>
#include            <vector>
#include            <iostream>
#include            <fstream>
#include            <unordered_map>
#include            "Database/Research.hpp"
#include            "Database/Int.hpp"
#include            "Database/String.hpp"
#include            "Database/Float.hpp"
#include            "Database/Bool.hpp"

class Bdd : public AObject {
private:
    std::string _title;
    int _lineIndex;
    std::string getObjectJSON(std::string &str) const;
    std::string getTitleJSON(std::string const &str) const;
    std::mutex _mtx;

protected:
    std::unordered_map<std::string, IObject *> _items;
    void addObject(std::string const &name, IObject *object);
    void parseJSON(std::string const &str);

public:
    explicit Bdd (std::string const &fileName, ToDo todo, bool isArray = false);
    explicit Bdd(const Bdd &obj);
    virtual ~Bdd();
    Bdd     &operator=(const Bdd &obj);
    int getValue();
    std::string const getType();
    IObject *     operator()(std::string const &pos) const;
    IObject *     operator()(int pos) const;
    Bdd *     operator[](std::string const &name);
    std::string const &getTitle() const;
    void setTitle(std::string const &title);
    void deleteObject(std::string const &name);
    int getValue() const;
    std::string getType() const;
    std::string getJSON() const;
    void save(std::string const &fileName);
    bool empty() const;
    IObject *copyObject() const;
    int addLine(IObject *tmp);
    virtual bool isEqual (Research object) const;
    std::vector<IObject *> find(std::vector<Research> research) const;
    bool contain(std::vector<Research> research) const;
    void lock();
    void unlock();
    std::string getRealJSON(std::string const &name, bool display = true) const;
    bool isArray() const;
    void setArray(bool value);
    static Bdd *singleton;

};

#else

    class Bdd;

#endif /* !Bdd_HHP_ */
