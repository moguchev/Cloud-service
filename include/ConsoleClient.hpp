// Copyright 2019 (c) <Cloud9>
#ifndef INCLUDE_CONSOLECLIENT_HPP_
#define INCLUDE_CONSOLECLIENT_HPP_
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

    ConsoleClient(permissions_t&& permissions) explicit;

    ConsoleClient(const permissions_t& permissions) explicit;

    static ConsoleClient CreateDefault();

    virtual void RunCommand(const std::string& com);

    virtual void SetProfile(const UserData& profile);

    virtual void ExpandPermissions();

private:
    UserData user_;
};
#endif  // INCLUDE_CONSOLECLIENT_HPP_
