// Copyright 2019 (c) <Cloud9>
#include "Commands.hpp"

namespace cmd {
    bool CommandParser::parse(const std::string& command) {
        args_t lexemes = getLexemes(command);
        if (lexemes.size() == 0)
            return false;

        command_ = lexemes[0];
        if (COMMANDS.find(command_) == COMMANDS.end())
            return false;

        args_.reserve(lexemes.size() - 1);
        args_.clear();

        //  Expression: cannot seek vector iterator after end
        //  std::copy(lexemes.begin() + 1, lexemes.end(), args_.begin());
        args_ = lexemes;
        args_.erase(args_.begin());

        if (!analyse())
            return false;

        return true;
    }

    std::string CommandParser::GetCommand() const noexcept {
        return command_;
    }

    args_t CommandParser::GetArgs() const noexcept {
        return args_;
    }

    args_t CommandParser::getLexemes(const std::string& str) {
        std::stringstream ss(str);
        std::string lexeme;
        args_t lexemes;
        while (ss >> lexeme) {
            lexemes.push_back(lexeme);
        }
        return lexemes;
    }

    bool CommandParser::analyse() {
        auto it = COMMANDS.find(command_);
        if (it != COMMANDS.end()) {
            return it->second(args_);
        }
        return false;
    }
}
