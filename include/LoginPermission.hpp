#pragma once
#include <iostream>
#include "AbstractClient.hpp"
#include "Commands.hpp"
#include "Permission.hpp"


UserData* logining(std::istream& in, std::ostream& out);

class LoginPermission : public Permission {
public:
    LoginPermission() = delete;
    virtual ~LoginPermission() = default;

    LoginPermission(std::istream& in, std::ostream& out)
        : istream_(&in)
        , ostream_(&out)
    {}

    virtual bool CanHandle(const std::string& com) {
        if (com == cmd::LOGIN)
            return true;
        return false;
    }

    virtual std::string Handle(const std::vector<std::string>& args) {
        
        auto userData = logining(*istream_, *ostream_);
        if (rightOwner_ != nullptr) {
            rightOwner_->SetProfile(*userData);
            rightOwner_->ExpandPermissions();
        }
        delete userData;
        return "success";
    }

    virtual void SetOwner(AbstractClient* client) {
        rightOwner_ = client;
    }
protected:
    AbstractClient* rightOwner_;
private:
    std::istream* istream_;
    std::ostream* ostream_;
};

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
