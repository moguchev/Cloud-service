#pragma once
#include <iostream>
#include <vector>
#include "AbstractClient.hpp"
#include "Commands.hpp"
#include "Permission.hpp"

UserData* registration(std::istream& in, std::ostream& out);

class CreateAccountPermission : public Permission {
public:
    CreateAccountPermission() = delete;
    virtual ~CreateAccountPermission() = default;

    CreateAccountPermission(std::istream& in, std::ostream& out)
        : istream_(&in)
        , ostream_(&out)
    {}

    virtual bool CanHandle(const std::string& com) {
        if (com == cmd::CREATE_ACCOUNT)
            return true;
        return false;
    }

    virtual std::string Handle(const std::vector<std::string>& args) {
        auto userData = registration(*istream_, *ostream_);
        std::vector<std::string> body = { userData->username, userData->mail, userData->password };
        // auto status = sendPostRequest(body);
        /* while (!status) {
            *ostream_ << status.what() << std::endl;
            userdata = registration(*istream_, *ostream_);
            std::vector<std::string> body = { userdata->username, userdata->mail, userdata->password };
            status = sendpostrequest(body);
        }*/

        // if success
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
    AbstractClient* rightOwner_ = nullptr;
private:
    std::istream* istream_;
    std::ostream* ostream_;
};

UserData* registration(std::istream& in, std::ostream& out) {
    auto user = new UserData;
    out << "Enter your username: ";
    in >> user->username;
    out << "Enter your email: ";
    in >> user->mail;
    // email checker
    // ...
    // 
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