// Copyright 2019 (c) <Cloud9>
#ifndef CONSOLECLIENT_HPP
#define CONSOLECLIENT_HPP
#include <list>
#include <string>
#include "Commands.hpp"
#include "AbstractClient.hpp"
#include "CreateAccountPermission.hpp"
#include "LoginPermission.hpp"
#include "DownloadPermission.hpp"

permissions_t BasicPermissions();

class ConsoleClient : public AbstractClient {
public:
    ConsoleClient() = default;

    ConsoleClient(permissions_t&& permissions);

    ConsoleClient(const permissions_t& permissions);

    static ConsoleClient CreateDefault();

    virtual void RunCommand(const std::string& com);

    virtual void SetProfile(const UserData& profile);

    virtual void ExpandPermissions();

private:
    UserData user_;
};

#endif  // CONSOLECLIENT_HPP