
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
#include "Server.hpp"


int main(int argc, char *argv[]) {
    Server serv;
    serv.startServer();
    return 0;
}
