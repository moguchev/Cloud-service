//
// Created by Андронов Дмитрий on 2019-05-26.

#include "classes.hpp"
#include <cstddef>
//#include <File.hpp>
Download::Download (std::string& login , std::string& password):login_(login) , password_(password) {
}


//Condition Download::execute() {
//    std::cout  << ">DOWNLOAD: OK" << std::endl;
//    std::cout << "login: "<< login_ << std::endl;
//    std::cout << "password: "<< password_ << std::endl;
//    return Condition::OK;
//}

// USES CLASSES FROM Alexey TakeDataClass e.g 
//need to integrate

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
