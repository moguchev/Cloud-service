// Copyright 2019 (c) <Cloud9>
#ifndef CLOUD_SERVICE_CREATEACCOUNTPERMISSION_HPP_
#define CLOUD_SERVICE_CREATEACCOUNTPERMISSION_HPP_
#include <iostream>
#include <vector>
#include <set>
#include "AbstractClient.hpp"
#include "Commands.hpp"
#include "Permission.hpp"

UserData* registration(std::istream& in, std::ostream& out);

class CreateAccountPermission : public Permission {
public:
    CreateAccountPermission() = delete;
    virtual ~CreateAccountPermission() = default;

    CreateAccountPermission(std::istream& in, std::ostream& out);

    virtual bool CanHandle(const std::string& com);

    virtual std::string Handle(const std::vector<std::string>& args);

    virtual void SetOwner(AbstractClient* client);
protected:
    AbstractClient* rightOwner_ = nullptr;
private:
    std::istream* istream_;
    std::ostream* ostream_;
};

#endif  // CLOUD_SERVICE_CREATEACCOUNTPERMISSION_HPP_