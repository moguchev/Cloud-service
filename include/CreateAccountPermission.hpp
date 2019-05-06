// Copyright 2019 (c) <Cloud9>
#ifndef CREATEACCOUNTPERMISSION_HPP
#define CREATEACCOUNTPERMISSION_HPP
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

    virtual bool CanHandle(const std::string& com);

    virtual std::string Handle(const std::vector<std::string>& args);

    virtual void SetOwner(AbstractClient* client) {
        rightOwner_ = client;
    }
protected:
    AbstractClient* rightOwner_ = nullptr;
private:
    std::istream* istream_;
    std::ostream* ostream_;
};

#endif  // CREATEACCOUNTPERMISSION_HPP