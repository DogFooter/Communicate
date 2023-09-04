#include "INamedPipeIPC.h"


DWORD INamedPipeIPC::WriteToPipe(ProgressData& data) {
    DWORD bytesWritten;
    if (!WriteFile(hPipe, &data, sizeof(data), &bytesWritten, NULL)) {
        return 0;
    }
    return bytesWritten;
}

DWORD INamedPipeIPC::WriteToPipe(InitialData& data) {
    DWORD bytesWritten;
    if (!WriteFile(hPipe, &data, sizeof(data), &bytesWritten, NULL)) {
        return 0;
    }
    return bytesWritten;
}

DWORD INamedPipeIPC::WriteToPipe(ResultData& data) {
    DWORD bytesWritten;
    if (!WriteFile(hPipe, &data, sizeof(data), &bytesWritten, NULL)) {
        return 0;
    }

    std::cout << " Finish" << std::endl;
    return bytesWritten;
}

DWORD INamedPipeIPC::ReadToPipe(ProgressData& data) {
    DWORD bytesRead;
    if (!ReadFile(hPipe, &data, sizeof(data), &bytesRead, NULL))
        return 0;

    data.print();
    return bytesRead;

}

DWORD INamedPipeIPC::ReadToPipe(InitialData& data) {
    DWORD bytesRead;
    if (!ReadFile(hPipe, &data, sizeof(data), &bytesRead, NULL))
        return 0;

    return bytesRead;

}

DWORD INamedPipeIPC::ReadToPipe(ResultData& data) {
    DWORD bytesRead;
    if (!ReadFile(hPipe, &data, sizeof(data), &bytesRead, NULL))
        return 0;

    std::cout << "Finished" << std::endl;
    return bytesRead;

}