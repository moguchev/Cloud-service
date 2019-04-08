//
// Created by Андронов Дмитрий on 2019-04-08.
//


#pragma once
#include <iostream>
#include <any>
#include <map>
#include <string>
#include <vector>

#include "Alexey_backend.hpp"


enum class Condition {OK , ERROR};

class AbstractControllerCommand {
public:
    virtual Condition execute () = 0;
    virtual ~AbstractControllerCommand() = default;
};


class AbstractRequest {
public:
    virtual std::string getBody() = 0;
    virtual std::string setBody() = 0;
    virtual ~AbstractRequest() = default;
};

class AbstractResponse {
public:
    virtual std::string getBody() = 0;
    virtual std::string setBody() = 0;
    virtual ~AbstractResponse() = default;
};


class AbstractRestServer {
public:
    virtual bool getRequest (AbstractRequest* request) = 0;
    virtual bool sendResponse () = 0;
    virtual ~AbstractRestServer() = default;
};



class AbstractController {
public:
    virtual bool execute_command() = 0;
    virtual void set_command(AbstractControllerCommand* command) = 0;
    virtual ~AbstractController() = default;
};

