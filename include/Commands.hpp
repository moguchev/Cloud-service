#pragma once
#include <string>
#include <vector>

namespace cmd {
    const std::string CREATE_ACCOUNT = "createaccount";
    const std::string DOWNLOAD = "download";
    const std::string UPLOAD = "upload";
    const std::string MERGE = "merge";
    const std::string LOGIN = "login";

    std::vector<std::string> COMMANDS = { LOGIN, CREATE_ACCOUNT, DOWNLOAD, UPLOAD, MERGE };
}

class CommandChecker {
    // как в бусте

};