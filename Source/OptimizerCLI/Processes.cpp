#include "Processes.h"
#include "Tools.h"
#include <string>
#include <iostream>
#include "NtProcessFunctions.h"
#include "Log.h"

bool ProcessManager::ReadProcesses(Settings* CSettings)
{
	if (GetProcessPIDs(CSettings)) return true;
	else
	{
		ERRORLOG("GetProcessPIDs failed");
		return false;
	}
}

bool ProcessManager::ReadFreezedProcesses()
{
	std::ifstream freezed;
	std::string freezedDirPath = Tools::RemoveExeFromPath(Tools::GetCurrentExePath());
	std::string freezedFilePath = freezedDirPath + "\\freezed.txt";
	freezed.open(freezedFilePath);
	if (freezed.fail())
	{
		ERRORLOG("Failed to open freezed.txt");
		return false;
	}

	std::string line;
	while (getline(freezed, line))
	{
		if (line.length() < 2) continue;
		PIDsFreezed.push_back(std::stoi(line));
	}
	return true;
}

void ProcessManager::StopProcesses()
{
	for (auto& PID : PIDsToStop)
	{
		HANDLE Handle;
		Handle = OpenProcess(PROCESS_ALL_ACCESS, false, PID);
		if (!TerminateProcess(Handle, 1))
		{
			LOG("TerminateProcess failed on PID " + std::to_string(PID));
		}
		else LOG("Terminated process with PID " + std::to_string(PID));
		CloseHandle(Handle);
	}
}

bool ProcessManager::InitializeExportsWrap()
{
	return InitializeExports();
}

bool ProcessManager::FreezeProcesses()
{
	std::string freezedDirPath = Tools::RemoveExeFromPath(Tools::GetCurrentExePath());
	std::string freezedFilePath = freezedDirPath + "\\freezed.txt";
	std::remove(freezedFilePath.c_str());	
	
	HANDLE Handle;
	WINDOWPLACEMENT* lpwndpl = new WINDOWPLACEMENT;
	lpwndpl->length = sizeof(WINDOWPLACEMENT);
	lpwndpl->showCmd = SW_MINIMIZE; 
	

	for (auto& PID : PIDsToFreeze)
	{
		Handle = OpenProcess(PROCESS_ALL_ACCESS, false, PID);
		HWND hCurWnd = nullptr; 
		do
		{
			hCurWnd = FindWindowEx(nullptr, hCurWnd, nullptr, nullptr);
			DWORD checkProcessID = 0;
			GetWindowThreadProcessId(hCurWnd, &checkProcessID);
			if (checkProcessID == PID)
			{
				SetWindowPlacement(hCurWnd, lpwndpl);
			}
		} while (hCurWnd != nullptr);
		
		
		if (SuspendProcess(Handle))
		{
			LOG("Freezed process with PID " + std::to_string(PID));
			PIDsFreezed.push_back(PID);
		}
		else
		{
			LOG("Failed to freeze process with PID " + std::to_string(PID));
		}
		CloseHandle(Handle);
	}
	return true;
}

void ProcessManager::ResumeProcesses()
{
	for (auto& PID : PIDsFreezed)
	{
		HANDLE Handle;
		Handle = OpenProcess(PROCESS_ALL_ACCESS, false, PID);
		if (!ResumeProcess(Handle))
		{
			LOG("ResumeProcess failed on PID " + std::to_string(PID));
		}
		else LOG("Resumed process with PID " + std::to_string(PID));
		CloseHandle(Handle);
	}
}

void ProcessManager::LowerProcesses()
{
	for (auto& PID : PIDsToLower)
	{
		HANDLE Handle;
		Handle = OpenProcess(PROCESS_SET_INFORMATION, false, PID);
		if (!SetPriorityClass(Handle, BELOW_NORMAL_PRIORITY_CLASS))
		{
			LOG("SetPriorityClass failed on PID " + std::to_string(PID));
		}
		else LOG("Lowered priority of process with PID " + std::to_string(PID));
		CloseHandle(Handle);
	}
}

void ProcessManager::Clean(Settings* CSettings)
{
	LOG("Cleaning ProcessManager, populating freezed.txt and adding OptimizerGUI to stopList.");
	PIDsToStop.clear();
	PIDsToFreeze.clear();
	PIDsToLower.clear();
	//PIDsFreezed.clear();
	CSettings->freezeList.clear();
	CSettings->lowerList.clear();
	CSettings->stopList.clear();
	CSettings->stopList.emplace_back("OptimizerGUI.exe");
	
	std::string freezedDirPath = Tools::RemoveExeFromPath(Tools::GetCurrentExePath());
	std::string freezedFilePath = freezedDirPath + "\\freezed.txt";
	std::remove(freezedFilePath.c_str());
	if (PIDsFreezed.empty()) return;
	std::ofstream freezed;
	freezed.open(freezedFilePath.c_str());
	for (auto& PID : PIDsFreezed)
	{
		freezed << PID << "\n";
	}
	freezed.close();
}

bool ProcessManager::GetProcessPIDs(Settings* CSettings)
{
		HANDLE hProcessSnap;
		PROCESSENTRY32 pe32;
		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hProcessSnap == INVALID_HANDLE_VALUE)
		{
			return(FALSE);
		}
		pe32.dwSize = sizeof(PROCESSENTRY32);

		if (!Process32First(hProcessSnap, &pe32))
		{
			CloseHandle(hProcessSnap);
			return(FALSE);
		}

		do
		{
			std::string ProcessName = Tools::Wide2String(pe32.szExeFile);
			if (std::find(CSettings->stopList.begin(), CSettings->stopList.end(), ProcessName) != CSettings->stopList.end())
			{
				DWORD PID = pe32.th32ProcessID;
				LOG("Adding process " + ProcessName + " from stopList to PIDsToStop with PID " + std::to_string(PID));
				PIDsToStop.push_back(PID);
			}
			else if (std::find(CSettings->freezeList.begin(), CSettings->freezeList.end(), ProcessName) != CSettings->freezeList.end())
			{
				DWORD PID = pe32.th32ProcessID;
				LOG("Adding process " + ProcessName + " from freezeList to PIDsToFreeze with PID " + std::to_string(PID));
				PIDsToFreeze.push_back(PID);
			}
			else if (std::find(CSettings->lowerList.begin(), CSettings->lowerList.end(), ProcessName) != CSettings->lowerList.end())
			{
				DWORD PID = pe32.th32ProcessID;
				LOG("Adding process " + ProcessName + " from lowerList to PIDsToLower with PID " + std::to_string(PID));
				PIDsToLower.push_back(PID);
			}
		} while (Process32Next(hProcessSnap, &pe32));

		CloseHandle(hProcessSnap);
		return(TRUE);
}
