#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <locale>
#include <codecvt>
#include <Windows.h>
#include <chrono>
#include <ctime>
#include "Settings.h"

namespace Tools
{
	bool ReadConfig(Settings* CSettings);
	std::string Wide2String(const std::wstring& wstr);
	std::wstring String2Wide(const std::string& str);
	inline std::wstring convertNarrowToWideStringEx(const std::string& as);
	HRESULT CreateShortcut(std::string pszTargetfile, std::string pszLinkfile, std::string pszCurdir);
	std::string GetCurrentExePath();
	std::string GetStartupFolderPath();
	std::string RemoveExeFromPath(std::string Path);
	BOOL StartProcess(std::string Path, DWORD priority);
	BOOL IsElevated();
	const char* currentTime();
}