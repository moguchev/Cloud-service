// Copyright 2019 (c) <Cloud9>
#ifndef INCLUDE_PERMISSION_HPP_
#define INCLUDE_PERMISSION_HPP_
#include <string>
#include <vector>

class AbstractClient;

class Permission {
public:
    Permission() = default;
    virtual bool CanHandle(const std::string& com) = 0;
    virtual std::string Handle(const std::vector<std::string>& com) = 0;
    virtual void SetOwner(AbstractClient* client) = 0;
    virtual ~Permission() = default;
};
#endif  // INCLUDE_PERMISSION_HPP_
