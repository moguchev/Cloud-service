// Copyright 2019 (c) <Cloud9>
#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>


namespace cmd {
    const std::string CREATE_ACCOUNT = "createaccount";
    const std::string DOWNLOAD = "download";
    const std::string UPLOAD = "upload";
    const std::string MERGE = "merge";
    const std::string LOGIN = "login";

    std::set<std::string> COMMANDS = { CREATE_ACCOUNT, DOWNLOAD, UPLOAD, LOGIN, MERGE };

    class CommandParser {
    public:
        CommandParser() = default;
        ~CommandParser() = default;

        bool parse(const std::string& command);

        std::string GetCommand() const noexcept;

        std::vector<std::string> GetArgs() const noexcept;
    private:
        std::string command_;
        std::vector<std::string> args_;

        std::vector<std::string> getLexemes(const std::string& str);

        bool analyse();
    };
}

#endif  // COMMANDS_HPP