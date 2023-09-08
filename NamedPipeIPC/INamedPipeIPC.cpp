#include "INamedPipeIPC.h"

template<typename T>
DWORD INamedPipeIPC::WriteToPipe(T& data) {
    DWORD bytesWritten;
    if (!WriteFile(hPipe, &data, sizeof(data), &bytesWritten, NULL)) {
        return 0;
    }
    return bytesWritten;
}


template<typename T>
DWORD INamedPipeIPC::ReadToPipe(T& data) {
    DWORD bytesRead;
    if (!ReadFile(hPipe, &data, sizeof(data), &bytesRead, NULL))
        return 0;

    data.print();
    return bytesRead;

}