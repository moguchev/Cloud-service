//
// Created by Андронов Дмитрий on 2019-05-26.
//

#pragma once
#include <string>

struct File{
    std::string name_;
    std::string body_;
    File (std::string name , std::string body): name_(name) , body_(body){}
};

enum class Condition {OK , ERROR};

class AbstractControllerCommand {
public:
    virtual Condition execute () = 0;
    virtual ~AbstractControllerCommand() = default;
};

class AbstractController {
public:
    virtual bool execute_command() = 0;
    virtual void set_command(std::string& commandName,
                             std::string& login,
                             std::string& password,
                             std::vector<File>& files) = 0;
    virtual ~AbstractController() = default;
};



