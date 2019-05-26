//
// Created by Андронов Дмитрий on 2019-05-26.
//
#include "boost/asio.hpp"
#include <functional>
#include <iostream>
#include <memory>
#include <thread>
#include <string>

#include "boost/bind.hpp"
#include <boost/function.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "classes.hpp"
#include "Connection.hpp"

class Server {
private:
    boost::asio::io_service m_Service;
    boost::asio::ip::tcp::acceptor m_Acceptor;

    void onAccept(std::shared_ptr<Client> c, const boost::system::error_code &e);
    void startAccept();
    void run();
public:
    Server();
    void startServer();
};