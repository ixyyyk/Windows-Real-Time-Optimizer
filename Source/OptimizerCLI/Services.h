#pragma once
#include <vector>
#include <string>
#include "Settings.h"

class ServiceManager
{
public:
	bool ReadServices(Settings* CSettings);
	void StopServices(Settings* CSettings);
	bool BackupServices(Settings* CSettings);
	bool RestoreServices(bool quiet);
private:
	std::vector<std::string> ServicesToStopManual;
	std::vector<std::string> ServicesToStopDisabled;
	std::vector<std::string> ServicesToRestoreAutomatic;
	std::vector<std::string> ServicesToRestoreManual;
};