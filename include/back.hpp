// Copyright 2019 (c) <Cloud9>

#ifndef INCLUDE_BACK_HPP_
#define INCLUDE_BACK_HPP_

#include "virtual_back.hpp"
#include <unordered_map>
#include <string>

std::any mergeAny(const std::any& root, const std::any& merging);

template <typename T>
class DataBase : public AbstractDataBase {
private:
    T _database;

public:
    Note* get(const std::string &root) override {
        if (_database.find(root) != _database.end()) {
            return &_database[root];
        } else {
            return nullptr;
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
        database->makeNote(_root, Note(_data));
    }
    ~Load() override = default;
};

class Merge : public AbstractCommand {
    std::string _root;
    std::string _merging;

public:
    Merge(const std::string& root, const std::string& merging) {
        _root = root;
        _merging = merging;
    }
    void execute(AbstractDataBase* database)  const override {
        Note* root = database->get(_root);
        Note* merging = database->get(_merging);

        std::any mergedAny = mergeAny(root->GetData(), merging->GetData());
        Note newNote = Note(mergedAny);

        root->data = newNote.data;
        database->deleteNote(_merging);
    }

    ~Merge() override = default;
};

class Delete : public AbstractCommand {
    std::string _root;

public:
    explicit Delete(const std::string& root) {
        _root = root;
    }
    void execute(AbstractDataBase* database)  const override {
        database->deleteNote(_root);
    }

    ~Delete() override = default;
};

class Change : public AbstractCommand {
    std::string _root;
    std::any _data;

public:
    Change(const std::string& root, const std::any& data) {
        _root = root;
        _data = data;
    }
    void execute(AbstractDataBase* database)  const override {
        Note* note = database->get(_root);
        note->data = _data;
    }
    ~Change() override = default;
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
