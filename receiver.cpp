#include "CNamedPipeIPC.h"

#include <windows.h>

#include <iostream>

#include "commData.h"

int main(int argc, char* argv[]) {
	// TODO: Get initData from arguments

	HANDLE hPipe;

	do {
		hPipe = CreateFile(TEXT("\\\\.\\pipe\\MyPipe"), GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_EXISTING, FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_BACKUP_SEMANTICS, NULL);
	} while (hPipe == INVALID_HANDLE_VALUE);

	/*if (hPipe == INVALID_HANDLE_VALUE) {
		std::cerr << "CreateFile failed" << std::endl;
		return -1;
	}*/

	InitialData initData;
	DWORD bytesRead;
	if (!ReadFile(hPipe, &initData, sizeof(initData), &bytesRead, NULL));
	while (true) {
		int i = 0;
		ProgressData progData = { i,i + 2,i + 4 };

		DWORD bytesWritten;
		if (!WriteFile(hPipe, &progData, sizeof(progData), &bytesWritten, NULL)) break;
		// If you want to receive data from the server at this point:
		// ReadFile(hPip&datatoreceivesizeof(datatoreceive)&bytesReaNULL);
		i++;
	}
	ResultData resData = {/*TODO: fill this with result data*/ };
	DWORD bytesWritten;
	if (!WriteFile(hPipe, &resData, sizeof(resData), &bytesWritten, NULL)) {
		CloseHandle(hPipe);
		return -1;
	}
	CloseHandle(hPipe);
	return(0);

}