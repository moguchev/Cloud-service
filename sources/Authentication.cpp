//
// Created by Андронов Дмитрий on 2019-05-04.
//
#pragma once
#include "classes.hpp"

Authentication::Authentication (std::string& login , std::string& password):login_(login) , password_(password) {
}

Condition Authentication::execute() {
    auto checkLoginCommand = isExistUser(login_);
    Condition condition = checkLoginCommand.execute();
    if (condition == Condition::ERROR)
        return Condition ::ERROR;
    TakePassClass TakePass(login_);
    std::string passwordFromDb;
    receiver(&TakePass , passwordFromDb);
    if (password_ != passwordFromDb)
        return Condition::ERROR;
    return Condition ::OK;
}


