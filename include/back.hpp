#ifndef UNTITLED4_HEADER_H
#define UNTITLED4_HEADER_H

#include "virtual_back.h"

class MyDataBase : public DataBase {
public:
    std::any get(const std::any& data) {
        if (_database.find(data) != _database.end()) {
            return _database[data];
        }
        else {
            return std::make_any(nullptr);
        }
    }

    void make_note(const std::any& root, const std::any& data) {
        _database[root] = data;
    }

    void delete_note(const std::any& data) {
        auto it = _database.find(data);

        if ( it != _database.end()) {
            _database.erase(it);
        }
    }

    ~DataBase() {}
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
    bool execute (const DataBase* database) {
        database->make_note(_root, _data);
    }
};

class MyReceiver : public Receiver {
public:
    bool operator()(Command* command) {
        command->execute(myDataBase);
    }
    ~Receiver() {}
};

MyReceiver myReceiver;
#endif //UNTITLED4_HEADER_H