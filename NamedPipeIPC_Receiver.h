#pragma once

#ifndef NAMEDPIPEIPC_RECEIVE_H
#define NAMEDPIPEIPC_RECEIVE_H


#include <windows.h>
#include <string>
#include <iostream>
#include "INamedPipeIPC.h"

class NamedPipeIPC_Receiver final : public INamedPipeIPC {


public:

    int CreateNamedPipeDefault(std::string_view s = "\\\\.\\pipe\\MyPipe") override;

    int Connection() override {};

};
#endif // !NAMEDPIPEIPC_RECEIVE_H