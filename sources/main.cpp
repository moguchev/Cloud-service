// Copyright 2019 (c) <Cloud9>
#define _SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING
// #define _CRTDBG_MAP_ALLOC
// #define new new( _NORMAL_BLOCK, __FILE__, __LINE__)
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include "ConsoleClient.hpp"


int main() {
    /*_CrtMemState _ms;
    _CrtMemCheckpoint(&_ms);
    {
        auto client = ConsoleClient::CreateDefault();
        client.RunCommand("login");
        client.RunCommand("createaccount");
    }
    _CrtMemDumpAllObjectsSince(&_ms);*/

    auto client = ConsoleClient::CreateDefault();
    client.RunCommand("login");
    client.RunCommand("createaccount");
    return 0;
}
