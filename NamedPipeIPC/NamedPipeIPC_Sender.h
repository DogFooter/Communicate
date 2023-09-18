#pragma once
#ifndef NAMEDPIPEIPC_SEND_H
#define NAMEDPIPEIPC_SEND_H


#include <windows.h>
#include <string>
#include <iostream>
#include "INamedPipeIPC.h"

class NamedPipeIPC_Sender final: public INamedPipeIPC {


public:

    int CreateNamedPipeDefault(std::string_view s = "") override;

    int Connection() override;


};
#endif // !NAMEDPIPEIPC_SEND_H