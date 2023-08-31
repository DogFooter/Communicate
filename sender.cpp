#include <windows.h>

#include <iostream>

#include "data.h"
int main() {
    InitialData initData = { 1, 2, 3, "Hello" };
    // TODO: Pass initData to b.exe
    HANDLE hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\MyPipe"), PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
        1, sizeof(ProgressData), sizeof(ResultData),
        NMPWAIT_USE_DEFAULT_WAIT, NULL);
    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "CreateNamedPipe failed" << std::endl;
        return -1;
    }
    DWORD bytesWritten;

    if (!ConnectNamedPipe(hPipe, NULL)) {
        CloseHandle(hPipe);
        std::cerr << "ConnectNamedPipe failed" << std::endl;
        return -1;
    }
    if (!WriteFile(hPipe, &initData, sizeof(initData), &bytesWritten, NULL)) {
        CloseHandle(hPipe);
        return -1;
    }
    std::cout << "Waiting for client" << std::endl;
    while (true) {
        ProgressData progData;
        DWORD bytesRead;
        if (!ReadFile(hPipe, &progData, sizeof(progData), &bytesRead, NULL)) break;

        progData.print();
        // TODO: Do something with progDat  
        // If you want to send data back to the client at this point:
        // WriteFile(hPip&datatosendsizeof(datatosend)&bytesWritteNULL);  
    }
    ResultData resData;
    DWORD bytesRead;
    if (!ReadFile(hPipe, &resData, sizeof(resData), &bytesRead, NULL)) {
        CloseHandle(hPipe);
        return -1;
    }
    // TODO: Do something with resDat
    CloseHandle(hPipe);
    return(0);

}