#include "NamedPipeIPC_Sender.h"



int main() {

    NamedPipeIPC_Sender Sender;

    Sender.CreateNamedPipeDefault();
    Sender.Connection();
    std::cout << "Connected !" << std::endl;


    InitialData initData = { 1, 2, 3, "Hello" };
    Sender.WriteToPipe(initData);


    ProgressData data;
    while (!Sender.ReadToPipe(data));


    ResultData resData;
    if (!Sender.ReadToPipe(resData)) {
        std::cout << "Receive Faild" << std::endl;
    }

    return 0;
}