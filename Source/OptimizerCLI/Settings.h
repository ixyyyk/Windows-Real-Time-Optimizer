#pragma once
#include <vector>
#include <string>
#include <Windows.h>

class Settings
{
public:
	//[SERVICES]
	bool DISABLE_ALL_INTERNET = false;
	bool DISABLE_WIRELESS_INTERNET = false;
	bool DISABLE_BLUETOOTH = false;
	bool DISABLE_AUDIO = false;
	bool USING_NOTEBOOK = true;
	//[OS]
	bool RUN_OS_TWEAKS = false;
	bool TURN_OFF_WINDOWS_DEFENDER = false;
	bool TURN_OFF_WINDOWS_FIREWALL = false;
	bool UNINSTALL_DEFAULT_WINDOWS_APPS = false;
	//[SETTINGS]
	bool NO_PERMANENT_CHANGES = true;
	bool CREATE_SERVICES_RESTORE_FILE = true;
	bool AUTO_APPLY_CONFIG = false;
	bool AUTO_START_GUI = false;
	bool QUIET_OUTPUT = false;
	bool EXIT_AFTER_APPLYING = false;
	//[PROCESSES]
	bool DISABLE_DESKTOP_ENVIRONMENT = false; //redundant
	bool LOWER_NON_CRITICAL_PROCESSES = false; //redundant
	//[PROCESSES_LIST]
	std::vector<std::string> stopList;
	std::vector<std::string> freezeList;
	std::vector<std::string> lowerList;
	//[START_LIST]
	std::vector<std::pair<std::string, DWORD>> startList;
};