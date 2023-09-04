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

public:

    virtual int CreateNamedPipeDefault(std::string_view s) = 0;
    virtual int Connection() = 0;


    virtual DWORD WriteToPipe(ProgressData& data);
    virtual DWORD WriteToPipe(InitialData& data);
    virtual DWORD WriteToPipe(ResultData& data);

    virtual DWORD ReadToPipe(ProgressData& data);
    virtual DWORD ReadToPipe(InitialData& data);
    virtual DWORD ReadToPipe(ResultData& data);

    virtual ~INamedPipeIPC() {
        CloseHandle(hPipe);
        std::cout << "Named Pipe cloesd" << std::endl;
    }


};

#endif // !I_NAMED_PIPE_IPC_H
