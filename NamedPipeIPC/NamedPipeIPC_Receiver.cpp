#include "NamedPipeIPC_Receiver.h"

int NamedPipeIPC_Receiver::CreateNamedPipeDefault(std::string_view pipeName) {

    if (pname.empty()) {
        pname = pipeName;
    }
    auto str = (pipePath + pipeName);
    std::wstring wstr(str.begin(), str.end());

    do {
        hPipe = CreateFile(wstr.data(), GENERIC_READ | GENERIC_WRITE,
            0, NULL, OPEN_EXISTING, FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_BACKUP_SEMANTICS, NULL);
    } while (hPipe == INVALID_HANDLE_VALUE);

    return 0;

}
