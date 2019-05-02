// Copyright 2019 (c) <Cloud9>
#define _CRTDBG_MAP_ALLOC 
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__)
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include "ConsoleClient.hpp"

int main() {
    _CrtMemState _ms;
    _CrtMemCheckpoint(&_ms);
    {
        auto client = ConsoleClient::CreateDefault();
        client.RunCommand("login");
        client.RunCommand("createaccount");
    }
    _CrtMemDumpAllObjectsSince(&_ms);
    system("pause");
    return 0;
}
