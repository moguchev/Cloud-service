//
// Created by Андронов Дмитрий on 2019-05-04.
//

#pragma once
#include "classes.hpp"

Registration::Registration (std::string& login , std::string& password):login_(login) , password_(password) {
}

Condition Registration::execute() {
    if (login_.empty() || password_.empty()) {
        std::cerr << "you have empty poles";
        return Condition::ERROR;
    }
    if (isExistUser(login_).execute() == Condition::OK) {
        std::cerr << "user with this username existed yet";
        return Condition ::ERROR;
    }
    AddUserClass addUser(login_ , password_);
    bool condition = false;
    receiver(&addUser, condition);
    if (condition)
        return Condition::OK;
    return Condition ::ERROR;
}