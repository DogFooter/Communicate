#include "CNamedPipeIPC.h"

int CNamedPipeIPC::CreateNamedPipeDefault(std::string_view s) {

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

int CNamedPipeIPC::Connection() {

    if (!ConnectNamedPipe(hPipe, NULL)) {
        std::cerr << "ConnectNamedPipe failed" << std::endl;
        return -1;
    }
    return 0;
}

DWORD CNamedPipeIPC::WriteToPipe(ProgressData& data) {
    DWORD bytesWritten;
    if (!WriteFile(hPipe, &data, sizeof(data), &bytesWritten, NULL)) {
        return 0;
    }
    return bytesWritten;
}

DWORD CNamedPipeIPC::WriteToPipe(InitialData& data) {
    DWORD bytesWritten;
    if (!WriteFile(hPipe, &data, sizeof(data), &bytesWritten, NULL)) {
        return 0;
    }
    return bytesWritten;
}

DWORD CNamedPipeIPC::WriteToPipe(ResultData& data) {
    DWORD bytesWritten;
    if (!WriteFile(hPipe, &data, sizeof(data), &bytesWritten, NULL)) {
        return 0;
    }

    std::cout << " Finish" << std::endl;
    return bytesWritten;
}

DWORD CNamedPipeIPC::ReadToPipe(ProgressData& data) {
    DWORD bytesRead;
    if (!ReadFile(hPipe, &data, sizeof(data), &bytesRead, NULL))
        return 0;

    data.print();
    return bytesRead;

}

DWORD CNamedPipeIPC::ReadToPipe(InitialData& data) {
    DWORD bytesRead;
    if (!ReadFile(hPipe, &data, sizeof(data), &bytesRead, NULL))
        return 0;

    return bytesRead;

}

DWORD CNamedPipeIPC::ReadToPipe(ResultData& data) {
    DWORD bytesRead;
    if (!ReadFile(hPipe, &data, sizeof(data), &bytesRead, NULL))
        return 0;

    std::cout << "Finished" << std::endl;
    return bytesRead;

}