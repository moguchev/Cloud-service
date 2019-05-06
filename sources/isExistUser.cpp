//
// Created by Андронов Дмитрий on 2019-05-04.
//

#pragma once
#include "classes.hpp"

isExistUser::isExistUser (std::string& login):login_(login){
}

Condition isExistUser::execute() {
    FindUserClass FindUser(login_); // search in Database in the near future
    volatile bool condition = false;
    receiver(&FindUser, condition);
    if (condition)
        return Condition ::OK;
    return Condition ::ERROR;
}



