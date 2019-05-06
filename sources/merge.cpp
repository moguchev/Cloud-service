//
// Created by Андронов Дмитрий on 2019-05-06.
//


#pragma once
#include "classes.hpp"
Merge::Merge(std::string& login , std::string& password , std::vector<std::string>& files) :
    login_(login) , password_(password), files_(files){
}

Condition Merge::execute() {
    if (Authentication(login_, password_).execute() == Condition::ERROR) {
        std::cerr << "wrong login or password" << std::endl;
        return Condition::ERROR;
    }
    std::vector<File> changedFiles = ChangedFilesToMerge(files_); //get changed files
    Change change(login_ , changedFiles);
    bool condtion = false;
    receiver(&change , condtion);
    if (!condtion)
        return Condition::ERROR;
    return Condition ::OK;

}

