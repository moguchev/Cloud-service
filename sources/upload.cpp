//
// Created by Андронов Дмитрий on 2019-05-26.
//

#include "classes.hpp"

Upload::Upload(std::string& login , std::string& password) : login_(login) , password_(password){
}

//Condition Upload::execute() {
//    std::cout  << ">UPLOAD: OK" << std::endl;
//    std::cout << "login: "<< login_ << std::endl;
//    std::cout << "password: "<< password_ << std::endl;
//    return Condition::OK;
//}


// USES CLASSES FROM Alexey GetPassClass
//need to integrate

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

