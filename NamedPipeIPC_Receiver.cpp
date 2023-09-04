#include "NamedPipeIPC_Receiver.h"

int NamedPipeIPC_Receiver::CreateNamedPipeDefault(std::string_view s) {

    do {
        hPipe = CreateFile(std::wstring(s.begin(), s.end()).data(), GENERIC_READ | GENERIC_WRITE,
            0, NULL, OPEN_EXISTING, FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_BACKUP_SEMANTICS, NULL);
    } while (hPipe == INVALID_HANDLE_VALUE);


    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "CreateNamedPipe failed" << std::endl;
        return -1;
    }
    return 0;

}
