#pragma once
#include <iostream>
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
        
        return "success";
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