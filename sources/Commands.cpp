// Copyright 2019 (c) <Cloud9>
#include "Commands.hpp"

namespace cmd {

    bool CommandParser::parse(const std::string& command) {
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

    std::string CommandParser::GetCommand() const {
        return command_;
    }

    std::vector<std::string> CommandParser::GetArgs() const {
        return args_;
    }

    std::vector<std::string> CommandParser::getLexemes(const std::string& str) {
            std::stringstream ss(str);
            std::string lexeme;
            std::vector<std::string> lexemes;
            while (ss >> lexeme) {
                lexemes.push_back(lexeme);
            }
            return lexemes;
        }

        bool CommandParser::analyse() {
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
}
