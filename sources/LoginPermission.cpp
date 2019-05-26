// Copyright 2019 (c) <Cloud9>
#include "LoginPermission.hpp"


LoginPermission::LoginPermission(std::istream& in, std::ostream& out)
    : istream_(&in)
    , ostream_(&out)
{}

bool LoginPermission::CanHandle(const std::string& com) {
    if (com == cmd::LOGIN)
        return true;
    return false;
}

std::string LoginPermission::Handle(const std::vector<std::string>& args) {
    auto userData = logining(*istream_, *ostream_);
    if (rightOwner_ != nullptr) {
        rightOwner_->SetProfile(*userData);
        rightOwner_->ExpandPermissions();
    }
    delete userData;
    return "success";
}

void LoginPermission::SetOwner(AbstractClient* client) {
    rightOwner_ = client;
}

UserData* logining(std::istream& in, std::ostream& out) {
    auto user = new UserData;
    out << "Enter your login: ";
    in >> user->mail;
    out << "Enter your password: ";
    std::string password;
    in >> password;
    user->password = password;
    return user;
}
