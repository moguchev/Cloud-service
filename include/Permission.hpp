#ifndef PERMISSION_HPP
#define PERMISSION_HPP
#include <string>

class AbstractClient;

class Permission {
public:
    Permission() = default;
    virtual bool CanHandle(const std::string& com) = 0;
    virtual std::string Handle(const std::vector<std::string>& com) = 0;
    virtual void SetOwner(AbstractClient* client) = 0;
    virtual ~Permission() = default;
};

#endif  // PERMISSION_HPP