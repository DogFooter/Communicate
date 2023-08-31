#pragma once

#include <iostream>

// Structure for initial data to be passed to receiver

struct InitialData {
	int arg1;
	int arg2;
	int arg3;
	std::string arg4;

};

// Structure for progress updates from receiver to sender

struct ProgressData {
	int progress1;
	int progress2;
	int progress3;
	void print() {
		std::cout << progress1 << " " << progress2 << " " << progress3 << std::endl;
	}

};
// Structure for final result from receiver to sender

struct ResultData {
	std::string resultStr;
	int resultCode;

};
