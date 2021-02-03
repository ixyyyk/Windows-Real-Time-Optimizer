#include "Log.h"
#include "Tools.h"
std::string logPath = Tools::RemoveExeFromPath(Tools::GetCurrentExePath());
std::ofstream LogFile(logPath + "\\log.txt");
bool quiet = false;

void Log::write(const char* msg)
{
	LogFile << msg << std::endl;
	if (quiet) return;
	std::cout << msg << std::endl;
}

void Log::write(std::string msg)
{
	LogFile << msg << std::endl;
	if (quiet) return; 
	std::cout << msg << std::endl;
}

void Log::error(const char* msg)
{
	LogFile << msg << std::endl;
	if (quiet) return;
	std::cout << msg << std::endl;
	std::cout << "Do you wish to continue?" << std::endl;
	system("pause");
}

void Log::error(std::string msg)
{
	LogFile << msg << std::endl;
	if (quiet) return;
	std::cout << msg << std::endl;
	std::cout << "Do you wish to continue?" << std::endl;
	system("pause");
}

void Log::InitConfig(bool quiet_output)
{
	quiet = quiet_output;
	if (quiet == true)
	{
		system("cls");
		system("@echo off");
	}
}

void Log::Hello()
{
	LogFile << "\n\n\n\n\n";
	LOG("***************************");
	LOG("WINDOWS REAL TIME OPTIMIZER");
	LOG(Tools::currentTime());
	LOG("***************************");
}

void Log::Goodbye()
{
	if (quiet) return;
	LOG(Tools::currentTime());
	ERRORLOG("WINDOWS REAL TIME OPTIMIZER FINISHED");
}
