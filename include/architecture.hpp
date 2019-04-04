// Copyright 2019 (c) <Cloud9>

#pragma once
#include <any>
#include <map>
#include <string>

//////////////////////////////////////////////////////////////////
// уровень пользовательского интерфейса///////////////////////////
//////////////////////////////////////////////////////////////////
class AbstractClient {
public:
    virtual void login(
        const std::string& login,
        const std::string& password
    ) = 0;
    virtual std::map<std::string, std::any> 
        show(const std::string& what) = 0;
    virtual bool download(const std::string& what) = 0;
    virtual bool upload(const std::string& what) = 0;
    virtual ~AbstractClient() = 0;
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
    virtual void handle_messege() = 0;
    virtual ~Resolver() = 0;
};

//////////////////////////////////////////////////////////////////
// сетевой уровень ///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

class RestClient {
public:
    virtual void handle_response() = 0;
    virtual void handle_request() = 0;
    virtual ~RestClient() = 0;
};

class RestServer {
public:
    virtual void handle_request() = 0;
    virtual ~RestServer() = 0;
};

class Request {
public:
    virtual void get_body() = 0;
    virtual void set_body() = 0;
    virtual ~Request() = 0;
};

class Response {
public:
    virtual void get_body() = 0;
    virtual void set_body() = 0;
    virtual ~Response() = 0;
};

//////////////////////////////////////////////////////////////////
// бизнес уровень ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

class Command {
    virtual void execute() = 0;
    virtual ~Command() = 0;
};

class Controller {
    Command* _command;
public:
    virtual void set_command(const Command& c) = 0;
    virtual ~Controller() = 0;
};


//////////////////////////////////////////////////////////////////
// уровень доступа к данным //////////////////////////////////////
//////////////////////////////////////////////////////////////////


class Reciver {
    virtual void operator()(const Command& c) = 0;
    virtual ~Reciver() = 0;
};


//////////////////////////////////////////////////////////////////
// БД ////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
