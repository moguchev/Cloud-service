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


class Client: public std::enable_shared_from_this<Client> {
private:
    boost::asio::ip::tcp::socket m_Sock;
    char m_Buf[1024];
    char m_SendBuf[1024];
    Controller *controller;
    UserInfo userInfo;
public:
    Client(boost::asio::io_service &io);
    boost::asio::ip::tcp::socket& sock();
    void get_request();
    void send_request();
    void handleRead(const boost::system::error_code& e, std::size_t bytes_transferred);
    Condition parseJson(const char* buff);
};