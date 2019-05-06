//
// Created by Андронов Дмитрий on 2019-05-05.
//

#pragma once
#include "classes.hpp"
Upload::Upload(std::string& login , std::string& password) : login_(login) , password_(password){
}

Condition Upload::execute() {
    if (Authentication(login_, password_).execute() == Condition::ERROR) {
        std::cerr << "wrong login or password" << std::endl;
        return Condition::ERROR;
    }
    TakeDataClass TakeData(login_);
    std::vector<cloud::File> files = receiver(&TakeData , files);
    std::vector<cloud::File> changedFiles = giveNewAndChangedFiles(files);
    Response().setBody(changedFiles);
    return Condition ::OK;
}

