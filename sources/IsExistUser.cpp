#include "classes.hpp"

isExistUser::isExistUser (std::string& login): login_(login){
}

// USES CLASSES FROM Alexey
//need to integrate
Condition isExistUser::execute() {
    FindUserClass FindUser(login_); // search in Database in the near future
    volatile bool condition = false;
    receiver(&FindUser, condition);
    if (condition)
        return Condition ::OK;
    return Condition ::ERROR;
}
//Condition isExistUser::execute() {
//    std::cout << ">Is_Exist_User: OK" << std::endl;
//    std::cout << "login: " << login_ << std::endl;
//    return Condition::OK;
//}