// Copyright 2019 (c) <Cloud9>

#pragma once
#include <any>
#include <map>
#include <string>

//////////////////////////////////////////////////////////////////
// уровень пользовательского интерфейса///////////////////////////
//////////////////////////////////////////////////////////////////
class Resolver;

class AbstractClient {
public:
    virtual void login(
        const std::string& login,
        const std::string& password) = 0;
    virtual void logout() = 0;
    virtual void run(const std::string& command) = 0;
    virtual void set_resolver(const Resolver* res) = 0;
private:
    Resolver* resolver_ = nullptr;
};

class ConsoleClient : public  AbstractClient {
public:
    void write_to_console();
    void read_from_console();
};

//////////////////////////////////////////////////////////////////
// прикладной уровень ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

class Resolver {
public:
    virtual void handle_command(const std::string& command) = 0;
    virtual std::string get_answer() = 0;
};

//////////////////////////////////////////////////////////////////
// сетевой уровень ///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

class Rest_client {
public:
    virtual std::string handle_request() = 0;
    virtual std::string handle_response() = 0;
};

class Rest_server {
public:
    virtual std::string handle_request() = 0;
};

class Request {
public:
    virtual std::string get_body() = 0;
    virtual std::string set_body() = 0;
};

class Response {
public:
    virtual std::string get_body() = 0;
    virtual std::string set_body() = 0;
};
