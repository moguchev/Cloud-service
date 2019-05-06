//
// Created by Андронов Дмитрий on 2019-05-05.
//

#pragma once
#include "classes.hpp"
#include <cstddef>
#include <File.hpp>
Download::Download (std::string& login , std::string& password):login_(login) , password_(password) {
}


Condition Download::execute() {
    if (Authentication(login_, password_).execute() == Condition::ERROR) {
        std::cerr << "wrong login or password" << std::endl;
        return Condition::ERROR;
    }
    TakeDataClass TakeData(login_);

     std::vector<cloud::File> files = receiver(&TakeData , files);
    Response().setBody(files); // set files to response
    return Condition ::OK;
}
