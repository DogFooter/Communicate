#pragma once
#ifndef NAMEDPIPEIPC_H
#define NAMEDPIPEIPC_H


#include <windows.h>
#include <string>
#include <iostream>
#include "commData.h"
class CNamedPipeIPC final{


    HANDLE hPipe = INVALID_HANDLE_VALUE;

public:

    int CreateNamedPipeDefault(std::string_view s = "\\\\.\\pipe\\MyPipe");

    int Connection();

    DWORD WriteToPipe(ProgressData& data);
    DWORD WriteToPipe(InitialData& data);
    DWORD WriteToPipe(ResultData& data);

    DWORD ReadToPipe(ProgressData& data);
    DWORD ReadToPipe(InitialData& data);
    DWORD ReadToPipe(ResultData& data);

    ~CNamedPipeIPC() {
        CloseHandle(hPipe);
        std::cout << "Named Pipe cloesd" << std::endl;
    }
};
#endif // !NAMEDPIPEIPC_H