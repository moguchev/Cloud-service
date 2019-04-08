// Copyright 2019 (c) <Cloud9>

#ifndef INCLUDE_VIRTUAL_BACK_HPP_
#define INCLUDE_VIRTUAL_BACK_HPP_
#include <map>
#include <any>

class DataBase {
public:
    virtual std::any get(const std::any& data) = 0;
    virtual void make_note(const std::any& root, const std::any& data) = 0;
    virtual void delete_note(const std::any& str) = 0;
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

#endif //INCLUDE_VIRTUAL_BACK_HPP_
