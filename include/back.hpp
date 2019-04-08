// Copyright 2019 (c) <Cloud9>

#ifndef INCLUDE_BACK_HPP_
#define INCLUDE_BACK_HPP_

#include "virtual_back.hpp"
#include <map>

class MyDataBase : public DataBase {
private:
    std::map<std::any, std::any> _database;


public:
    std::any get(const std::any& data) {
        if (_database.find(data) != _database.end()) {
            return _database[data];
        } else {
            return std::make_any(nullptr);
        }
    }

    void make_note(const std::any& root, const std::any& data) {
        _database[root] = data;
    }

    void delete_note(const std::any& data) {
        auto it = _database.find(data);

        if (it != _database.end()) {
            _database.erase(it);
        }
    }

    ~MyDataBase() {}
};

MyDataBase myDataBase;

class Load : public Command {
    std::any _root;
    std::any _data;

public:
    Load(const std::any& root, const std::any& data) {
        _root = root;
        _data = data;
    }
    void execute(const DataBase* database) const {
        database->make_note(_root, _data);
    }
    ~Load() {}
};

class MyReceiver : public Receiver {
public:
    void operator()(Command* command) const {
        command->execute(&myDataBase);
    }
    ~MyReceiver() {}
};

MyReceiver myReceiver;
#endif //INCLUDE_BACK_HPP_
