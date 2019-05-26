// Copyright 2019 (c) <Cloud9>
#ifndef CLOUD_SERVICE_NETWORKUTILS_HPP_
#define CLOUD_SERVICE_NETWORKUTILS_HPP_
#include <string>
#include "ClientHTTPS.hpp"

const auto HOST = "";
const auto POST_HOST = "";
const auto PORT = "";
const auto VERSION = 11;
const auto APPLICATION_JSON = "application/json";

namespace nu {

    std::string get_request_from_target(const std::string& target) {
        boost::asio::io_context io_service;
        ssl::context ctx(ssl::context::sslv23_client);
        ctx.set_default_verify_paths();

        auto request = std::make_shared<session>(io_service, ctx);
        request->GetRequest(HOST, PORT, target.c_str(), VERSION);
        io_service.run();

        return request->get_body();
    }

    std::string post_request_from_target(const std::string& target,

        const std::string& body) {
        boost::asio::io_context io_service;
        ssl::context ctx(ssl::context::sslv23_client);
        ctx.set_default_verify_paths();

        auto request = std::make_shared<session>(io_service, ctx);
        request->PostRequest(POST_HOST, PORT, target.c_str(), VERSION,
            APPLICATION_JSON, body);
        io_service.run();

        return request->get_body();
    }

#endif  // CLOUD_SERVICE_NETWORKUTILS_HPP_
