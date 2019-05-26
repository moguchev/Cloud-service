// Copyright 2019 (c) <Cloud9>
#ifndef CLOUD_SERVICE_CLIENTHTTPS_HPP_
#define CLOUD_SERVICE_CLIENTHTTPS_HPP_
#define _SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING

#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
using error_code = boost::system::error_code;

void fail(error_code ec, char const* what);

class session : public std::enable_shared_from_this<session> {
    tcp::resolver resolver_;
    ssl::stream<tcp::socket> stream_;
    boost::beast::flat_buffer buffer_;
    http::request<http::string_body> req_;
    http::response<http::string_body> res_;

public:
    explicit session(boost::asio::io_context& ioc, ssl::context& ctx)
        : resolver_(ioc), stream_(ioc, ctx) {}

    void GetRequest(char const* host, char const* port, char const* target, int version);

    void PostRequest(char const* host,
        char const* port,
        char const* target,
        int version,
        const std::string& content_type,
        const std::string& body);

    void on_resolve(error_code ec,
        tcp::resolver::results_type results);

    void on_connect(error_code ec);

    void on_handshake(error_code ec);

    void on_write(error_code ec, std::size_t bytes_transferred);

    void on_read(error_code ec, std::size_t bytes_transferred);

    void on_shutdown(error_code ec);

    std::string get_body();
};

#endif  // CLOUD_SERVICE_CLIENTHTTPS_HPP_