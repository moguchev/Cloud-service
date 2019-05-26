// Copyright 2019 (c) <Cloud9>
#ifndef CLOUD_SERVICE_DOWNLOADPERMISSION_HPP_
#define CLOUD_SERVICE_DOWNLOADPERMISSION_HPP_
#include <iostream>
#include <filesystem>
#include <fstream>
#include "AbstractClient.hpp"
#include "Commands.hpp"
#include "Permission.hpp"

class DownloadPermission : public Permission {
public:
    DownloadPermission() = default;
    virtual ~DownloadPermission() = default;

    DownloadPermission(std::istream& in, std::ostream& out)
        : istream_(&in)
        , ostream_(&out)
    {}

    virtual bool CanHandle(const std::string& com) {
        if (com == cmd::DOWNLOAD)
            return true;
        return false;
    }

    virtual std::string Handle(const std::vector<std::string>& args) {
        if (args.size() != 2)
            return "fail" ; // #TODO : function Handle should return special ErrorObject

        //auto status = sendGetResponse("download", args[0]);
        //if (!status())
        //    return "fail"; // #TODO : function Handle should return special ErrorObject
        //auto body = status.body();

        //std::filesystem::path file_path(args[1]);
        //
        //if (!std::filesystem::exists(file_path))
        //    return "fail"; // #TODO : function Handle should return special ErrorObject

        //for (const auto& f : body.files()) {
        //    std::filesystem::path file = file_path / f.name();
        //    std::ofstream ofs(file, std::ios::binary);
        //    ofs << f.binary_body;
        //    ofs.close();
        //}
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

#endif  // CLOUD_SERVICE_DOWNLOADPERMISSION_HPP_