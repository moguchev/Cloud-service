//
// Created by Андронов Дмитрий on 2019-05-06.
//
#pragma once
#include <classes.hpp>
#include <stdexcept>

Controller::Controller(AbstractReceiver& receiver): receiver_(receiver) {}

AbstractControllerCommand* Controller::set_command(std::string& commandName , std::string& login, std::string& password) {
    try {
            if(commandName == "Authentication") return new Authentication(login, password);
            if(commandName == "Registration") return new Registration(login, password);
            if(commandName == "Download") return new Download(login, password);
            if(commandName == "Upload") return new Upload(login, password);
            if(commandName == "Merge") return new Merge(login, password);
            throw std::invalid_argument("Not such command: " + commandName);
    }
    catch (std::invalid_argument ex){
        std::cout << "Caught an error!" << std::endl;
        std::cout << ex.what() << std::endl ;
    }
}


bool Controller::execute_command() {
    command_->execute();
}