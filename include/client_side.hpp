// Copyright 2019 (c) <Cloud9>

#pragma once
#include <any>
#include <map>
#include <string>
#include <iostream>
#include <exception>
#include <utility>

class Resolver {
public:
    virtual void handle_command(const std::string& command) = 0;
    virtual std::string get_answer() = 0;
    virtual ~Resolver() = 0;
};

class BasicResolver : public Resolver {
    virtual void handle_command(const std::string& command) {
        auto docommand = command /* logic */
    }

    virtual std::string get_answer() {
        return "answer";
    }
};

class AbstractClient {
 public:
    virtual bool login(const std::string& login,
        const std::string& password) = 0;
    virtual void logout() = 0;
    virtual std::string run(const std::string& command) = 0;
    virtual bool set_resolver(Resolver* res) = 0;
    virtual ~AbstractClient() = 0;

 protected:
    Resolver* resolver_ = nullptr;
};

bool check_command(const std::string& command) {
    return false;
}

class ConsoleClientDestroyer;

class ConsoleClient : public AbstractClient {
 public:
      static ConsoleClient& getInstance() {
          if (!p_instance) {
              p_instance = new ConsoleClient();
              destroyer_.initialize(p_instance);
          }
          return *p_instance;
      }

      virtual bool login(const std::string& login,
          const std::string& password) {
          user_ = std::make_pair(login, password);
          return true;
      }

      virtual void logout() {
          user_.first.clear();
          user_.second.clear();
      }

      virtual std::string run(const std::string& command) {
          if (resolver_ == nullptr)
              throw std::runtime_error("Resolver not found");
          resolver_->handle_command(command);
          return resolver_->get_answer();
      }

      virtual bool set_resolver(Resolver* resolver) {
          if (resolver != nullptr)
            resolver_ = resolver;
      }

      void write_to_console(const std::string& message) const {
          std::cout << message << std::endl;
      }

      void read_from_console() {
          while (std::cin.fail()) {
              std::cin >> buffer_;
              if (check_command(buffer_)) {
                  auto answer = run(buffer_);
                  write_to_console(answer);
              } else
                  write_to_console("no such command");
          }
          return;
      }

 protected:
      ConsoleClient() = default;
      ConsoleClient(const ConsoleClient& rhs) = delete;
      ConsoleClient(ConsoleClient&& rhs) = delete;
      ConsoleClient& operator=(const ConsoleClient& rhs) = delete;
      ConsoleClient& operator=(ConsoleClient&& rhs) = delete;
      virtual ~ConsoleClient() = default;

      std::pair<std::string, std::string> user_;
      std::string buffer_;
      Resolver* resolver_ = nullptr;

 private:
      static ConsoleClient* p_instance;
      static ConsoleClientDestroyer destroyer_;
      friend class ConsoleClientDestroyer;
};

class ConsoleClientDestroyer {
 private:
  ConsoleClient* p_instance = nullptr;

 public:
  ~ConsoleClientDestroyer() {
    if (p_instance != nullptr) delete p_instance;
  };

  void initialize(ConsoleClient* client) { p_instance = client; }
};

class RestClient {
 public:
  virtual std::string handle_request(const std::string& request) = 0;
  virtual ~RestClient() = 0;
};

class BoostHTTPClient : RestClient {
public:
    virtual std::string handle_request(const std::string& request) {
        return request;
    }
    ~BoostHTTPClient() = default;
};
