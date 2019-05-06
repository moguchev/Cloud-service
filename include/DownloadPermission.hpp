// Copyright 2019 (c) <Cloud9>
#ifndef DOWNLOADPERMISSION_HPP
#define DOWNLOADPERMISSION_HPP
#include <iostream>
#include "AbstractClient.hpp"
#include "Commands.hpp"
#include "Permission.hpp"

class DownloadPermission : public Permission {
public:
    DownloadPermission() = default;
    virtual ~DownloadPermission() = default;

    DownloadPermission(std::istream& in, std::ostream& out);

    virtual bool CanHandle(const std::string& com);

    virtual std::string Handle(const std::vector<std::string>& args);

    virtual void SetOwner(AbstractClient* client);
protected:
    AbstractClient* rightOwner_;
private:
    std::istream* istream_;
    std::ostream* ostream_;
};

#endif  // DOWNLOADPERMISSION_HPP