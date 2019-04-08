// Copyright 2019 (c) <Cloud9>

#ifndef INCLUDE_BACK_HPP_
#define INCLUDE_BACK_HPP_

#include "virtual_back.hpp"
#include <unordered_map>

class MyDataBase : public DataBase {
private:
    std::unordered_map<std::string, std::string> _database;

public:
    std::string get(const std::string& data) override {
        if (_database.find(data) != _database.end()) {
            return _database[data];
        } else {
            return "";
        }
    }

    void makeNote(const std::string &root, const std::string &data) override {
        _database[root] = data;
    }

    void deleteNote(const std::string &data) override {
        auto it = _database.find(data);

        if (it != _database.end()) {
            _database.erase(it);
        }
    }

    ~MyDataBase() override = default;
};

MyDataBase myDataBase;

class Load : public Command {
    std::string _root;
    std::string _data;

public:
    Load(const std::string& root, const std::string& data) {
        _root = root;
        _data = data;
    }
    void execute(DataBase* database)  const override {
        database->makeNote(_root, _data);
    }
    ~Load() override = default;
};

class MyReceiver : public Receiver {
public:
    void operator()(Command* command) const override {
        command->execute(&myDataBase);
    }
    ~MyReceiver() override = default;
};

MyReceiver myReceiver;
#endif //INCLUDE_BACK_HPP_
