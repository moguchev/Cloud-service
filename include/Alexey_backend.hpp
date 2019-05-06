//
// Created by Андронов Дмитрий on 2019-04-08.
//


#pragma once
#include <string>


class AbstractDataBase {
public:
    virtual std::string get(const std::string& data) const = 0;
    virtual void makeNote(const std::string& root,
                           const std::string& data) const = 0;
    virtual void deleteNote(const std::string& str) = 0;
    virtual ~AbstractDataBase() = default;
};

class AbstractCommand {
public:
    virtual void execute (const AbstractDataBase* database) const = 0;
    virtual ~AbstractCommand() = default;
};

class AbstractReceiver {
public:
    virtual void operator()(AbstractCommand* command) const = 0;
    virtual ~AbstractReceiver() = default;
};

class Receiver : AbstractReceiver{
    void operator()(AbstractCommand* command) const override ;
};
