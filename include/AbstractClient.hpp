// Copyright 2019 (c) <Cloud9>
#ifndef INCLUDE_ABSTRACTCLIENT_HPP_
#define INCLUDE_ABSTRACTCLIENT_HPP_
#include <list>
#include <string>
#include "Permission.hpp"

using permissions_t = std::list<Permission*>;

struct UserData {
  std::string username;
  std::string mail;
  std::string password;
};

class AbstractClient {
 public:
  AbstractClient() = default;
  virtual void SetProfile(const UserData& profile) = 0;
  virtual void RunCommand(const std::string& com) = 0;
  virtual void ExpandPermissions() = 0;
  virtual ~AbstractClient() {
    for (auto& permission : permissions_)
      if (permission != nullptr) delete permission;
  }

 protected:
  permissions_t permissions_;
};
#endif  // INCLUDE_ABSTRACTCLIENT_HPP_
