//
// Created by Андронов Дмитрий on 2019-05-26.
//
#include "classes.hpp"

Controller::Controller(): command_(nullptr) {
    receiver_ = new Receiver();
}
void Controller::set_command(std::string& commandName,
                            std::string& login,
                            std::string& password,
                             std::vector<File>& files){
    try {
        if(commandName == "Authentication") {
            command_ = new Authentication(login, password);
            return;
        }
        if(commandName == "Registration") {
            command_ = new Registration(login, password);
            return;
        }
        if(commandName == "isExistUser") {
            command_ = new isExistUser(login);
            return;
        }
        if(commandName == "download") {
            command_ = new Download(login , password);
            return;
        }
        if(commandName == "upload") {
            command_ = new Upload(login , password);
            return;
        }
        if(commandName == "merge") {
            command_ = new Merge (login , password , files);
            return;
        }

        throw std::invalid_argument("Not such command: " + commandName);
    }
    catch (std::invalid_argument& ex){
        std::cout << "Caught an error!" << std::endl;
        std::cout << ex.what() << std::endl ;
    }
}


bool Controller::execute_command() {
    command_->execute();
    return true;
}
