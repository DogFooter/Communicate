#include <windows.h>
#include <string>
#include <iostream>

#include "commData.h"
class CNamedPipeIPC {


    HANDLE hPipe = INVALID_HANDLE_VALUE;

public:

    int CreateNamedPipeDefault(std::string_view s = "\\\\.\\pipe\\MyPipe") {

        hPipe = CreateNamedPipe(std::wstring(s.begin(), s.end()).data(), PIPE_ACCESS_DUPLEX,
            PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
            1, sizeof(ProgressData), sizeof(ResultData),
            NMPWAIT_USE_DEFAULT_WAIT, NULL);


        if (hPipe == INVALID_HANDLE_VALUE) {
            std::cerr << "CreateNamedPipe failed" << std::endl;
            return -1;
        }
        return 0;

    }

    int Connection() {

        if (!ConnectNamedPipe(hPipe, NULL)) {
            std::cerr << "ConnectNamedPipe failed" << std::endl;
            return -1;
        }
        return 0;
    }

    DWORD WriteToPipe(ProgressData& data) {
        DWORD bytesWritten;
        if (!WriteFile(hPipe, &data, sizeof(data), &bytesWritten, NULL)) {
            return 0;
        }
        return bytesWritten;
    }

    DWORD WriteToPipe(InitialData& data) {
        DWORD bytesWritten;
        if (!WriteFile(hPipe, &data, sizeof(data), &bytesWritten, NULL)) {
            return 0;
        }
        return bytesWritten;
    }

    DWORD WriteToPipe(ResultData& data) {
        DWORD bytesWritten;
        if (!WriteFile(hPipe, &data, sizeof(data), &bytesWritten, NULL)) {
            return 0;
        }

        std::cout << " Finish" << std::endl;
        return bytesWritten;
    }

    DWORD ReadToPipe(ProgressData& data) {
        DWORD bytesRead;
        if (!ReadFile(hPipe, &data, sizeof(data), &bytesRead, NULL))
            return 0;

        data.print();
        return bytesRead;

    }

    DWORD ReadToPipe(InitialData& data) {
        DWORD bytesRead;
        if (!ReadFile(hPipe, &data, sizeof(data), &bytesRead, NULL))
            return 0;

        return bytesRead;

    }

    DWORD ReadToPipe(ResultData& data) {
        DWORD bytesRead;
        if (!ReadFile(hPipe, &data, sizeof(data), &bytesRead, NULL))
            return 0;

        std::cout << "Finished" << std::endl;
        return bytesRead;

    }
    ~CNamedPipeIPC() {
        CloseHandle(hPipe);
        std::cout << "Named Pipe cloesd" << std::endl;
    }
};

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