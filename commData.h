#pragma once

#include <iostream>

// Structure for initial data to be passed to receiver
struct ICommData {

	virtual void print() = 0;
};

struct InitialData : public ICommData {
	int arg1;
	int arg2;
	int arg3;
	std::string arg4;
	
	void print() {
		std::cout << arg1 << " " << arg2 << " " << arg3 << " " << arg4 << std::endl;
	}

};

// Structure for progress updates from receiver to sender

struct ProgressData :public ICommData {
	int progress1;
	int progress2;
	int progress3;
	void print() {
		std::cout << progress1 << " " << progress2 << " " << progress3 << std::endl;
	}

};
// Structure for final result from receiver to sender

struct ResultData : public ICommData {
	std::string resultStr;
	int resultCode;
	void print() {
		std::cout << "" << resultStr << " " << resultCode << std::endl;
	}

};
