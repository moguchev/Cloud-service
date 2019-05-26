//
// Created by Андронов Дмитрий on 2019-05-26.
//
#include <boost/foreach.hpp>
#include "Connection.hpp"


    Client::Client(boost::asio::io_service &io) : m_Sock(io) , controller(new Controller) {}
    boost::asio::ip::tcp::socket& Client::sock() { return m_Sock; }
    void Client::get_request() {
        m_Sock.async_read_some(boost::asio::buffer(m_Buf),
                               boost::bind(&Client::handleRead,
                                           shared_from_this(),
                                           boost::asio::placeholders::error,
                                           boost::asio::placeholders::bytes_transferred));
    }
    void Client::handleRead(const boost::system::error_code& e, std::size_t bytes_transferred)
    {
        if (e == boost::asio::error::eof)
        {
            std::cerr << "-client: " << m_Sock.remote_endpoint().address().to_string() << std::endl;
        }
        if (e) return;
        //std::cerr << "read: " << bytes_transferred << " bytes" << std::endl;
        parseJson(m_Buf);
        controller->execute_command();
        std::cout << "Get message: " << m_Buf << std::endl;
        send_request();
    }

    Condition Client::parseJson(const char* buff) {
        boost::property_tree::ptree pt;
        std::string ss = buff;
        std::istringstream is(ss);
        std::cout << ss << std::endl;
        read_json(is, pt);
        userInfo.login = pt.get<std::string>("login");
        userInfo.password = pt.get<std::string>("password");
        userInfo.command = pt.get<std::string>("command");
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child("files"))
        {
            userInfo.files.emplace_back(File(v.first.data() , v.second.data()));
        }
        controller->set_command(userInfo.command, userInfo.login, userInfo.password , userInfo.files);
        return Condition::OK;
    }

    void Client::send_request() {
        int k = snprintf(m_SendBuf, sizeof(m_SendBuf), "From Server: HTTP/1.1 200 OK\r\n");
        k += snprintf(m_SendBuf + k, sizeof(m_SendBuf) - k, "Content-Length:");
        k += snprintf(m_SendBuf + k, sizeof(m_SendBuf) - k, "\n o2proxy ready (ver. 0.1.3)\n");
        if (strcmp(m_Buf , "Hello") == 0)
            k += snprintf(m_SendBuf + k, sizeof(m_SendBuf) - k, "Hello FROM SERVER");
        else
            k += snprintf(m_SendBuf + k, sizeof(m_SendBuf) - k, m_Buf);
        k += snprintf(m_SendBuf + k, sizeof(m_SendBuf) - k, "\n End.\n");
        // need to Send files to user
        m_Sock.async_write_some(boost::asio::buffer(m_SendBuf),
                                [self = shared_from_this()](const boost::system::error_code& e, std::size_t bytes_transferred)->void
                                {
                                    std::cout << "Send to client" << std::endl;
                                    self->get_request();
                                });
    }