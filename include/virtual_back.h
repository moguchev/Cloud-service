//
// Created by Алексей on 2019-04-08.
//

#ifndef PROJECT_VIRTUAL_BACK_H
#define PROJECT_VIRTUAL_BACK_H
#include <map>
#include <any>

class DataBase {
private:
    std::map<std::any, std::any> _database;

public:
    virtual std::any get(const std::any& data) = 0;
    virtual bool make_note(const std::any& root, const std::any& data) = 0;
    virtual bool delete_note(const std::any& str) = 0;
    virtual ~DataBase() = 0;
};

class Command {
public:
    virtual bool execute(const DataBase* database) = 0;
    virtual ~Command() = 0;
};

class Receiver {
public:
    virtual bool operator()(Command* command) = 0;
    virtual ~Receiver() = 0;
};

#endif //PROJECT_VIRTUAL_BACK_H
