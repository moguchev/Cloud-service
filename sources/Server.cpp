//
// Created by Андронов Дмитрий on 2019-05-26.
//
#include "Server.hpp"

    void Server::onAccept(std::shared_ptr<Client> c, const boost::system::error_code& e) {
        if (e) return;

        std::cerr << "+client: " << c->sock().remote_endpoint().address().to_string().c_str() << std::endl;

        c->get_request();
        startAccept();
    }
    void Server::startAccept() {
        std::shared_ptr<Client> c(new Client(m_Service));
        m_Acceptor.async_accept(c->sock(), boost::bind(&Server::onAccept, this, c, boost::asio::placeholders::error));
    }
    void Server::run() { m_Service.run(); }

    Server::Server() : m_Acceptor(m_Service)    {}

    void Server::startServer() {
        int port = 5001;
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
        m_Acceptor.open(endpoint.protocol());
        m_Acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
        m_Acceptor.bind(endpoint);
        m_Acceptor.listen(1024);
        startAccept();

        std::cerr << "listen on port: " << port << std::endl;

        std::vector<std::thread> threads;
        for (int i = 0; i < 4; ++i)
            threads.push_back(std::thread(std::bind(&Server::run, this)));
        for (auto &thread: threads)
            thread.join();
    }