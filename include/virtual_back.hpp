// Copyright 2019 (c) <Cloud9>

#ifndef INCLUDE_VIRTUAL_BACK_HPP_
#define INCLUDE_VIRTUAL_BACK_HPP_
#include <string>
#include <any>

struct Note {
    std::any data;

    Note(const std::any& any = std::any(std::nullptr_t())) : data(any) {}
    Note(const Note& another) : data(another.data) {}

    Note& operator=(const std::any& any) {
        data = any;

        return *this;
    }

    Note& operator=(const Note& another) {
        data = another.data;

        return *this;
    }

    std::any& GetData() {
        return data;
    }
};

class AbstractDataBase {
public:
    virtual Note get(const std::string &root)  = 0;
    virtual void makeNote(const std::string &root,
                          const Note &data)  = 0;
    virtual void deleteNote(const std::string &root) = 0;
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
