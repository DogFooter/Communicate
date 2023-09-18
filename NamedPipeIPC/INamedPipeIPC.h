#pragma once
#pragma once
#ifndef I_NAMED_PIPE_IPC_H
#define I_NAMED_PIPE_IPC_H

#include <windows.h>
#include <string>
#include <iostream>
#include "commData.h"


class INamedPipeIPC
{
protected:
    HANDLE hPipe = INVALID_HANDLE_VALUE;
    constexpr std::string_view pipePath = "\\\\.\\pipe\\";
    std::string pipeName = "MyPipe";
public:

    virtual int CreateNamedPipeDefault(std::string_view s) = 0;
    virtual int Connection() = 0;

    template<typename T>
    virtual DWORD WriteToPipe(T& data);

    template<typename T>
    virtual DWORD ReadToPipe(T& data);

   
    virtual ~INamedPipeIPC() {
        CloseHandle(hPipe);
        std::cout << "Named Pipe cloesd" << std::endl;
    }


};

#endif // !I_NAMED_PIPE_IPC_H
