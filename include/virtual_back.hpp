// Copyright 2019 (c) <Cloud9>

#ifndef INCLUDE_VIRTUAL_BACK_HPP_
#define INCLUDE_VIRTUAL_BACK_HPP_
#include <string>

class AbstractDataBase {
public:
    virtual std::string get(const std::string& data)  = 0;
    virtual void makeNote(const std::string &root,
                          const std::string &data)  = 0;
    virtual void deleteNote(const std::string &data) = 0;
    virtual ~AbstractDataBase() = default;
};

class AbstractCommand {
public:
    virtual void execute(AbstractDataBase* database) const = 0;
    virtual ~AbstractCommand() = default;
};

class AbstractReceiver {
public:
    virtual void operator()(AbstractCommand* command) const = 0;
    virtual ~AbstractReceiver() = default;
};

#endif //INCLUDE_VIRTUAL_BACK_HPP_
