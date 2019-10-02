// Copyright 2019 (c) <Cloud9>
#include "ConsoleClient.hpp"
#include "DownloadPermission.hpp"
#include "UploadPermission.hpp"
#include "MergePermission.hpp"
#include "DeleteFilesPermission.hpp"

permissions_t BasicPermissions() {
    permissions_t permissions = {
         new DownloadPermission , new UploadPermission
         /*, new MergePermission, new DeleteFilesPermission */
    };
    return  permissions;
}

ConsoleClient::ConsoleClient(permissions_t&& permissions) {
    permissions_ = std::move(permissions);
    for (auto p : permissions_) {
        p->SetOwner(this);
    }
}

ConsoleClient::ConsoleClient(const permissions_t& permissions) {
    permissions_ = permissions;
    for (auto p : permissions_) {
        p->SetOwner(this);
    }
}

ConsoleClient ConsoleClient::CreateDefault() {
    permissions_t permissions;
    permissions.push_back(new CreateAccountPermission(std::cin, std::cout));
    permissions.push_back(new LoginPermission(std::cin, std::cout));
    return ConsoleClient(std::move(permissions));
}

void ConsoleClient::RunCommand(const std::string& com) {
    cmd::CommandParser command;
    if (!command.parse(com)) {
        // help window with commands
        return;
    }

    bool action = false;
    for (auto& p : permissions_) {
        if (p->CanHandle(command.GetCommand())) {
            auto status = p->Handle(command.GetArgs());
            std::cout << status << std::endl;
            action = true;
            break;
        }
    }

    if (!action) {
        // help window with permissions
        return;
    }
}

void ConsoleClient::SetProfile(const UserData& profile) {
    user_ = profile;
}

void ConsoleClient::ExpandPermissions() {
    auto newps = BasicPermissions();
    permissions_.insert(permissions_.end(), newps.begin(), newps.end());
}
