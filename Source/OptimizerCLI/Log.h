#pragma once
#include <iostream>
#include <fstream>

#define LOG(msg) Log::write(msg)
#define ERRORLOG(msg) Log::error(msg);

namespace Log
{
	void write(const char* msg);
	void write(std::string msg);
	void error(const char* msg);
	void error(std::string msg);
	void InitConfig(bool quiet);
	void Hello();
	void Goodbye();
}

