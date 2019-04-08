// Copyright 2019 (c) <Cloud9>

#ifndef INCLUDE_VIRTUAL_BACK_HPP_
#define INCLUDE_VIRTUAL_BACK_HPP_

class AbstractDataBase {
public:
    virtual std::string get(const std::string& data)  = 0;
    virtual void makeNote(const std::string &root,
                          const std::string &data)  = 0;
    virtual void deleteNote(const std::string &data) = 0;
    virtual ~AbstractDataBase() = 0;
};

class AbstractCommand {
public:
    virtual void execute(AbstractDataBase* database) const = 0;
    virtual ~AbstractCommand() = 0;
};

class AbstractReceiver {
public:
    virtual void operator()(AbstractCommand* command) const = 0;
    virtual ~AbstractReceiver() = 0;
};

#endif //INCLUDE_VIRTUAL_BACK_HPP_
