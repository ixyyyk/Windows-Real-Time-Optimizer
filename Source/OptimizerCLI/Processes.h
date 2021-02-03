#pragma once
#include <vector>
#include <string>
#include <process.h>
#include <windows.h>
#include <tlhelp32.h>
#include "Settings.h"

class ProcessManager
{
public:
	bool ReadProcesses(Settings* CSettings);
	bool ReadFreezedProcesses();
	void StopProcesses();
	bool InitializeExportsWrap();
	bool FreezeProcesses();
	void LowerProcesses();
	void Clean(Settings* CSettings);
	void ResumeProcesses();
private:
	std::vector<DWORD> PIDsToStop;
	std::vector<DWORD> PIDsToFreeze;
	std::vector<DWORD> PIDsToLower;
	std::vector<DWORD> PIDsFreezed;
	bool GetProcessPIDs(Settings* CSettings);
};