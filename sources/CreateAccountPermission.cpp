// Copyright 2019 (c) <Cloud9>
#include "CreateAccountPermission.hpp"

CreateAccountPermission::CreateAccountPermission(
    std::istream& in, std::ostream& out)
    : istream_(&in)
    , ostream_(&out)
{}

bool CreateAccountPermission::CanHandle(const std::string& com) {
    if (com == cmd::CREATE_ACCOUNT)
        return true;
    return false;
}

std::string CreateAccountPermission::Handle(
    const std::vector<std::string>& args) {
    auto userData = registration(*istream_, *ostream_);
    std::vector<std::string> body = {
        userData->username,
        userData->mail,
        userData->password
    };
    /*auto status = sendPostRequest(body);
    while (!status) {
        *ostream_ << status.what() << std::endl;
        auto userdata = registration(*istream_, *ostream_);
        std::vector<std::string> body = { userdata->username, userdata->mail, userdata->password };
        status = sendPostrequest(body);
    }*/

    // if success
    if (rightOwner_ != nullptr) {
        rightOwner_->SetProfile(*userData);
        rightOwner_->ExpandPermissions();
    }
    delete userData;
    return "success";
}

void CreateAccountPermission::SetOwner(AbstractClient* client) {
    rightOwner_ = client;
}

UserData* registration(std::istream& in, std::ostream& out) {
    auto user = new UserData;
    out << "Enter your username: ";
    in >> user->username;
    out << "Enter your email: ";
    in >> user->mail;
    // email checker
    // ...
    std::string password;
    do {
        out << "Enter your password: ";
        in >> user->password;
        out << "Enter your password again: ";
        in >> password;
        if (password != user->password)
            out << "Passwords do not match! ";
    } while (password != user->password);
    return  user;
}
