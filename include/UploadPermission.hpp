// Copyright 2019 (c) <Cloud9>
#ifndef INCLUDE_UPLOADPERMISSION_HPP_
#define INCLUDE_UPLOADPERMISSION_HPP_
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include "AbstractClient.hpp"
#include "Commands.hpp"
#include "Permission.hpp"

class UploadPermission : public Permission {
public:
    UploadPermission() = default;
    virtual ~UploadPermission() = default;

    UploadPermission(std::istream& in, std::ostream& out)
        : istream_(&in)
        , ostream_(&out)
    {}

    virtual bool CanHandle(const std::string& com) {
        if (com == cmd::UPLOAD)
            return true;
        return false;
    }

    virtual std::string Handle(const std::vector<std::string>& args) {
        if (args.size() != 2)
            return "fail";
        // #TODO : function Handle should return special ErrorObject

        std::filesystem::path file_path(args[0]);
        uintmax_t size = std::filesystem::file_size(file_path);

        std::string binary_body;

        std::ifstream ifs(file_path, std::ios::binary);

        if (ifs.is_open()) {
            binary_body =
                static_cast<std::stringstream const&>(std::stringstream() <<
                    ifs.rdbuf()).str();
            ifs.close();
        }

        std::vector<std::string> Body = {
            file_path.filename().string(),
            file_path.extension().string(),
            binary_body
        };
        //auto status = sendPostRequest("upload", Body, args[1]);
        //if (!status())
        //    return "fail";
        // #TODO : function Handle should return special ErrorObject
    }

    virtual void SetOwner(AbstractClient* client) {
        rightOwner_ = client;
    }

protected:
    AbstractClient* rightOwner_;

private:
    std::istream* istream_;
    std::ostream* ostream_;
};
#endif  // INCLUDE_UPLOADPERMISSION_HPP_
