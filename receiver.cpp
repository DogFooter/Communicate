#include "NamedPipeIPC_Receiver.h"


int main(int argc, char* argv[]) {
	// TODO: Get initData from arguments

	
	CNamedPipeIPC Receiver;
	Receiver.CreateNamedPipeDefault();

	InitialData initData;
	Receiver.ReadToPipe(initData);

	int i = 0;
	while ( i < 10 ) {
		ProgressData progData = { i,i + 2,i + 4 };

		if (!Receiver.WriteToPipe(progData))
			break;

		i++;
	}
	ResultData resData = {"Done", 0 };
	Receiver.WriteToPipe(resData);

	return 0;

}