// Copyright 2019 (c) <Cloud9>
#ifndef INCLUDE_COMMANDS_HPP_
#define INCLUDE_COMMANDS_HPP_
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <functional>


namespace cmd {
const auto CREATE_ACCOUNT = "createaccount";
const auto CREATE_BRANCH = "createbranch";
const auto CREATE_REPOSITORY = "createrepository";
const auto DOWNLOAD = "download";
const auto UPLOAD = "upload";
const auto MERGE = "merge";
const auto LOGIN = "login";
using args_t = std::vector<std::string>;

inline bool isEmptyArgs(const args_t& args) {
    if (args.size() == 0)
        return true;
    return false;
}
inline bool checkCrRepo(const args_t& args);
inline bool checkCrBranch(const args_t& args);
inline bool checkDownload(const args_t& args);
inline bool checkUpload(const args_t& args);
inline bool checkMerge(const args_t& args);

const std::map<std::string, std::function<bool(const args_t&)>> COMMANDS = {
    { CREATE_ACCOUNT, isEmptyArgs },
    { CREATE_REPOSITORY, checkCrRepo },
    { CREATE_BRANCH, checkCrBranch },
    { DOWNLOAD,  checkDownload },
    { UPLOAD, checkUpload },
    { LOGIN, isEmptyArgs },
    { MERGE, checkMerge }
};

const std::map<std::string, std::string> HELP_INFO_FOR_COMMANDS = {
    { CREATE_ACCOUNT, "unexpected arguments" },
    { CREATE_REPOSITORY, "<name>" },
    { CREATE_BRANCH, "<repo/name>" },
    { DOWNLOAD, "<repo/branch/directory/file><path-where>" },
    { UPLOAD, "<path><repo/branch|repo/branch/directory>" },
    { LOGIN, "unexpected arguments" },
    { MERGE, "<repo/branch>" }
};

}  // namespace cmd

namespace cmd {
class CommandParser {
public:
    CommandParser() = default;
    ~CommandParser() = default;

    bool parse(const std::string& command);

    std::string GetCommand() const noexcept;

    args_t GetArgs() const noexcept;
private:
    std::string command_;
    args_t args_;

    args_t getLexemes(const std::string& str);

    bool analyse();
};

}  // namespace cmd
#endif  // INCLUDE_COMMANDS_HPP_
