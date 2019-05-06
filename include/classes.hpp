//
// Created by Андронов Дмитрий on 2019-04-08.
//



#pragma once
#include "abstractClasses.hpp"
#include "File.hpp"
#include <vector>


class Request : public AbstractRequest {
public:
    std::string getBody() override ;
    std::string setBody() override ;
    ~Request() = default;
};

class Response : public AbstractResponse {
public:
     std::string getBody() override ;
     std::string setBody(std::vector<cloud::File>) override ;
     ~Response() = default;
};

class Authentication : public AbstractControllerCommand {
private:
    std::string& login_;
    std::string& password_;
public:
    explicit Authentication (std::string& login , std::string& password);
    Condition execute () override;
    ~Authentication ()= default;
};


class isExistUser : public AbstractControllerCommand {
private:
    std::string login_;
public:
    explicit isExistUser (std::string& login );
    Condition execute () override;
    ~isExistUser () = default;
};



class Registration : public AbstractControllerCommand {
private:
    std::string login_;
    std::string password_;
public:
    explicit Registration (std::string& login , std::string& password);
    Condition execute () override;
    ~Registration () = default;
};


class Download : public AbstractControllerCommand {
private:
    std::string login_;
    std::string password_;
public:
    explicit Download (std::string& login , std::string& password);
    Condition execute () override;
    ~Download () = default;
};

class Upload : public AbstractControllerCommand {
private:
    std::string login_;
    std::string password_;
public:
    explicit Upload (std::string& login , std::string& password);
    Condition execute () override;
    ~Upload () = default;
};


class Merge : public AbstractControllerCommand {
private:
    std::string login_;
    std::string password_;
    std::vector<std::string> files_;
public:
    explicit Merge (std::string& login , std::string& password , std::vector<std::string>& files);
    Condition execute () override;
    ~Merge () = default;
};




class Controller : public AbstractController {
private:
    AbstractReceiver& receiver_;
    AbstractControllerCommand* command_;
    Condition condition_;
public:
    explicit Controller (AbstractReceiver& receiver);

    bool execute_command() override ;

    AbstractControllerCommand* set_command(std::string& commandName ,
            std::string& login ,
            std::string&password ) override ;
    ~Controller() = default;
};

class RestServer : public AbstractRestServer {
public:
    explicit RestServer(Controller*);
    bool getRequest (AbstractRequest* request) override;
    bool sendResponse () override;
    ~RestServer();

private:
    std::vector<AbstractRequest> queueRequest_;
    Controller* controller_;
};


class File {
private:
    std::string name_;
    std::string type_;
    std::vector<std::byte> BinaryCode_;
public:
    std::string getName() const  {
        return name_;
    }
    std::string getType () const  {
        return type_;
    }
    std::vector<std::byte> getBody () const{
        return BinaryCode_;
    }


};