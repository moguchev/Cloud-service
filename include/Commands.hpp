#pragma once
#include <iostream>
#include <string>
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

        bool parse(const std::string& command) {
            auto lexemes = getLexemes(command);
            if (lexemes.size() == 0)
                return false;

            command_ = lexemes.at(0);
            if (COMMANDS.find(command_) == COMMANDS.end())
                return false;

            std::copy(lexemes.begin() + 1, lexemes.end(), args_.begin());

            /*if (!analyse())
                return false;*/
            return true;
        }

        std::string GetCommand() const noexcept {
            return command_;
        }

        std::vector<std::string> GetArgs() const noexcept {
            return args_;
        }
    private:
        std::string command_;
        std::vector<std::string> args_;

        std::vector<std::string> getLexemes(const std::string& str) {
            std::stringstream ss(str);
            std::string lexeme;
            std::vector<std::string> lexemes;
            while (ss >> lexeme) {
                lexemes.push_back(lexeme);
            }
            return lexemes;
        }

        bool analyse() {
            if (command_ == CREATE_ACCOUNT) {
                if (args_.size() == 0)
                    return true;
                return false;
            }
            if (command_ == LOGIN) {
                if (args_.size() == 0)
                    return true;
                return false;
            }
            if (command_ == DOWNLOAD) {
                // ... 
                return true;
            }
            if (command_ == UPLOAD) {
                // ... 
                return true;
            }
            if (command_ == MERGE) {
                // ... 
                return true;
            }
            return false;
        }
    };
}

