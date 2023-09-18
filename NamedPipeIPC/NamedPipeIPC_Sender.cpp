#include "NamedPipeIPC_Sender.h"

int NamedPipeIPC_Sender::CreateNamedPipeDefault(std::string_view pname) {
    if (pname.empty()) {
        pname = pipeName;
    }
    auto str = (pipePath + pipeName);
    std::wstring wstr(str.begin(), str.end());

    hPipe = CreateNamedPipe(wstr.data(), PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
        1, sizeof(ProgressData), sizeof(ResultData),
        NMPWAIT_USE_DEFAULT_WAIT, NULL);


    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "CreateNamedPipe failed" << std::endl;
        return -1;
    }
    return 0;

}

int NamedPipeIPC_Sender::Connection() {

    if (!ConnectNamedPipe(hPipe, NULL)) {
        std::cerr << "ConnectNamedPipe failed" << std::endl;
        return -1;
    }
    return 0;
}