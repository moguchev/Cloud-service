#pragma once
#include <string>

class AbstractClient;

class Permission {
public:
    Permission() = default;
    virtual bool CanHandle(const std::string& com) = 0;
    virtual std::string Handle(const std::string& com) = 0;
    virtual void SetOwner(AbstractClient* client) = 0;
    virtual ~Permission() = default;
};