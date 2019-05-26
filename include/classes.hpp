//
// Created by Андронов Дмитрий on 2019-05-26.
//

#pragma once

#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "AbstractClasses.hpp"
#include "receiver.hpp"



struct UserInfo {
    std::string login;
    std::string password;
    std::string command;
    std::vector<File> files;
};



// commands
class Authentication : public AbstractControllerCommand {
private:
    std::string& login_;
    std::string& password_;
public:
    explicit Authentication (std::string& login , std::string& password);
    Condition execute () override;
    ~Authentication() override = default;
};


class isExistUser : public AbstractControllerCommand {
private:
    std::string login_;
public:
    explicit isExistUser (std::string& login);
    Condition execute () override;
    ~isExistUser () override = default;
};

class Registration : public AbstractControllerCommand {
private:
    std::string login_;
    std::string password_;
public:
    explicit Registration (std::string& login , std::string& password);
    Condition execute () override;
    ~Registration () override = default;
};


class Download : public AbstractControllerCommand {
private:
    std::string login_;
    std::string password_;
public:
    explicit Download (std::string& login , std::string& password);
    Condition execute () override;
    ~Download () override = default;
};

class Upload : public AbstractControllerCommand {
private:
    std::string login_;
    std::string password_;
public:
    explicit Upload (std::string& login , std::string& password);
    Condition execute () override;
    ~Upload () override = default;
};


class Merge : public AbstractControllerCommand {
private:
    std::string& login_;
    std::string& password_;
    std::vector<File>& files_;
public:
    Merge (std::string& login , std::string& password , std::vector<File>& files);
    Condition execute () override;
    ~Merge () override = default;
};

class Controller : public AbstractController {
private:
    AbstractReceiver* receiver_;
    AbstractControllerCommand* command_;

public:
    Controller ();

    bool execute_command() override ;

    void set_command(std::string& commandName ,
                    std::string& login ,
                    std::string& password,
                     std::vector<File>& files) override ;
    ~Controller() override = default;
};



