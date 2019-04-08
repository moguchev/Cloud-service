//
// Created by Андронов Дмитрий on 2019-04-08.
//

//
// Created by Андронов Дмитрий on 2019-04-08.
//


#pragma once
#include "abstractClasses.hpp"

class Request : public AbstractRequest {
public:
    std::string getBody() override ;
    std::string setBody() override ;
    ~Request() = default;
};

class Response : public AbstractResponse {
public:
    virtual std::string getBody() override ;
    virtual std::string setBody() override ;
    virtual ~Response() = default;
};

class Authentication : public AbstractControllerCommand {
private:
    std::string login_;
    std::string password_;
public:
    explicit Authentication (std::string login , std::string password);
    Condition execute () override;
    std::string getLogin ();
    std::string getPassword();
    ~Authentication ()= default;
};


class isExistUser : public AbstractControllerCommand {
private:
    std::string login_;
public:
    explicit isExistUser (std::string login );
    Condition execute () override;
    std::string getLogin ();
    ~isExistUser () = default;
};



class Registration : public AbstractControllerCommand {
private:
    std::string login_;
    std::string password_;
public:
    explicit Registration (std::string login , std::string password);
    Condition execute () override;
    std::string getLogin ();
    std::string getPassword ();
    ~Registration () = default;
};


class Download : public AbstractControllerCommand {
private:
    std::string login_;
    std::string password_;
public:
    explicit Download (std::string login , std::string password);
    Condition execute () override;
    std::string getLogin ();
    std::string getPassword ();
    ~Download () = default;
};

class Upload : public AbstractControllerCommand {
private:
    std::string login_;
    std::string password_;
public:
    explicit Upload (std::string login , std::string password);
    Condition execute () override;
    std::string getLogin ();
    std::string getPassword ();
    ~Upload () = default;
};


class Merge : public AbstractControllerCommand {
private:
    std::string login_;
    std::string password_;
public:
    explicit Merge (std::string login , std::string password);
    Condition execute () override;
    std::string getLogin ();
    std::string getPassword ();
    ~Merge () = default;
};



class Controller : public AbstractController {
private:
    AbstractReceiver* receiver_;
    AbstractCommand* command_;
    Condition condition_;
public:
    explicit Controller (AbstractReceiver* receiver);

    bool execute_command() override ;

    void set_command(AbstractControllerCommand* command) override ;

    ~Controller() = default;
};

class RestServer : public AbstractRestServer {
public:
    explicit RestServer(Controller*);
    bool getRequest (AbstractRequest* request) override;
    bool sendResponse () override;
    bool pushRequest (AbstractRequest request);
    bool popRequest ();
    int sizeQueue ();
    ~RestServer();

private:
    std::vector<AbstractRequest> queueRequest_;
    Controller* controller_;
};
