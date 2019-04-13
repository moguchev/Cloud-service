// Copyright 2019 (c) <Cloud9>

#ifndef INCLUDE_BACK_HPP_
#define INCLUDE_BACK_HPP_

#include "virtual_back.hpp"
#include <unordered_map>
#include <string>

template <typename T>
class DataBase : public AbstractDataBase {
private:
    T _database;

public:

    Note get(const std::string &root) override {
        if (_database.find(root) != _database.end()) {
            return _database[root];
        } else {
            return Note();
        }
    }

    void makeNote(const std::string &root, const Note &data) override {
        _database[root] = data;
    }

    void deleteNote(const std::string &root) override {
        auto it = _database.find(root);

        if (it != _database.end()) {
            _database.erase(it);
        }
    }

    ~DataBase() override = default;
};

DataBase<std::unordered_map<std::string, Note>> myDataBase;

class Load : public AbstractCommand {
    std::string _root;
    std::any _data;

public:
    Load(const std::string& root, const std::any& data) {
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
