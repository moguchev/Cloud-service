// Copyright 2019 (c) <Cloud9>

#ifndef INCLUDE_BACK_HPP_
#define INCLUDE_BACK_HPP_

#include "virtual_back.hpp"
#include <unordered_map>
#include <string>

class DataBase : public AbstractDataBase {
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

    ~DataBase() override = default;
};

DataBase myDataBase;

class Load : public AbstractCommand {
    std::string _root;
    std::string _data;

public:
    Load(const std::string& root, const std::string& data) {
        _root = root;
        _data = data;
    }
    void execute(AbstractDataBase* database)  const override {
        database->makeNote(_root, _data);
    }
    ~Load() override = default;
};

class Receiver : public AbstractReceiver {
public:
    void operator()(AbstractCommand* command) const override {
        command->execute(&myDataBase);
    }
    ~Receiver() override = default;
};

Receiver myReceiver;
#endif //INCLUDE_BACK_HPP_
