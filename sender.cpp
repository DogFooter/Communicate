#include "CNamedPipeIPC.h"



int main() {

    InitialData initData = { 1, 2, 3, "Hello" };
    CNamedPipeIPC Sender;

    Sender.CreateNamedPipeDefault();
    Sender.Connection();;

    std::cout << "Waiting for client" << std::endl;

    ProgressData data;
    while (!Sender.ReadToPipe(data));

    ResultData resData;
    if (!Sender.ReadToPipe(resData)) {
        std::cout << "Receive Faild" << std::endl;
    }

    return 0;

}