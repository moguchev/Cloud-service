// Copyright 2019 (c) <Cloud9>

#ifndef INCLUDE_VIRTUAL_BACK_HPP_
#define INCLUDE_VIRTUAL_BACK_HPP_

class DataBase {
public:
    virtual std::string get(const std::string& data)  = 0;
    virtual void makeNote(const std::string &root,
                          const std::string &data)  = 0;
    virtual void deleteNote(const std::string &data) = 0;
    virtual ~DataBase() = 0;
};

class Command {
public:
    virtual void execute(DataBase* database) const = 0;
    virtual ~Command() = 0;
};

class Receiver {
public:
    virtual void operator()(Command* command) const = 0;
    virtual ~Receiver() = 0;
};

#endif //INCLUDE_VIRTUAL_BACK_HPP_
