//
// Created by Андронов Дмитрий on 2019-05-26.
//

//
// Created by Андронов Дмитрий on 2019-05-04.


#include "classes.hpp"

Authentication::Authentication (std::string& login , std::string& password):login_(login) , password_(password) {
}

//Condition Authentication::execute() {
//    std::cout  << ">AUTHENTICATION: OK" << std::endl;
//    std::cout << "login: "<< login_ << std::endl;
//    std::cout << "password: "<< password_ << std::endl;
//    return Condition::OK;
//}

// USES CLASSES FROM Alexey GetPassClass
//need to integrate

Condition Authentication::execute() {
    auto checkLoginCommand = isExistUser(login_);
    Condition condition = checkLoginCommand.execute();
    if (condition == Condition::ERROR)
        return Condition ::ERROR;
    GetPassClass GetPass(login_);
    std::string passwordFromDb;
    receiver(&GetPass , passwordFromDb);
    if (password_ != passwordFromDb)
        return Condition::ERROR;
    return Condition ::OK;
}


