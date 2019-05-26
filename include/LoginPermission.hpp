// Copyright 2019 (c) <Cloud9>
#ifndef INCLUDE_LOGINPERMISSION_HPP_
#define INCLUDE_LOGINPERMISSION_HPP_
#include <iostream>
#include <string>
#include <vector>
#include "AbstractClient.hpp"
#include "Commands.hpp"
#include "Permission.hpp"

UserData* logining(std::istream& in, std::ostream& out);

class LoginPermission : public Permission {
 public:
  LoginPermission() = delete;
  virtual ~LoginPermission() = default;

  LoginPermission(std::istream& in, std::ostream& out);

  virtual bool CanHandle(const std::string& com);

  virtual std::string Handle(const std::vector<std::string>& args);

  virtual void SetOwner(AbstractClient* client);

 protected:
  AbstractClient* rightOwner_;

 private:
  std::istream* istream_;
  std::ostream* ostream_;
};
#endif  // INCLUDE_LOGINPERMISSION_HPP_
