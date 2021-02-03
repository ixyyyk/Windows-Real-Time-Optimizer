#include "System.h"
#include "Settings.h"
#include "Log.h"
#include "Tools.h"
#include <fstream>
#include <Windows.h>
#include <shellapi.h>


void SystemManager::Init(Settings* CSettings)
{
	LOG("Removing old powershell.ps1");
	std::string pathExe = Tools::GetCurrentExePath();
	std::string pathDir = Tools::RemoveExeFromPath(pathExe); 
	std::string pathPowershell = pathDir + "\\powershell.ps1";
	std::remove(pathPowershell.c_str());

	std::ofstream powershell;
	LOG("Creating powershell.ps1");
	std::string pathScripts = pathDir + "\\scripts.ps1";
	powershell.open(pathPowershell);

	LOG("Using " + pathScripts + " as path to scripts.ps1");
	powershell << ". " << "\"" << pathScripts << "\"" << "\n"; //path to scripts.ps1
	
	
	if (CSettings->TURN_OFF_WINDOWS_DEFENDER)
	{
		LOG("TURN_OFF_WINDOWS_DEFENDER = True. Adding DisableDefender and DisableDefenderCloud.");
		powershell << "DisableDefender\n";
		powershell << "DisableDefenderCloud\n";
	}

	if (CSettings->TURN_OFF_WINDOWS_FIREWALL)
	{
		LOG("TURN_OFF_WINDOWS_FIREWALL = True. Adding DisableFirewall.");
		powershell << "DisableFirewall\n";
	}

	if (CSettings->UNINSTALL_DEFAULT_WINDOWS_APPS)
	{
		LOG("UNINSTALL_DEFAULT_WINDOWS_APPS = True. UninstallDefaultApps and UninstallWindowsStore.");
		powershell << "UninstallDefaultApps\n";
		powershell << "UninstallWindowsStore\n";
	}

	LOG("Adding RunDefaultFunctions.");
	//powershell << "RequireAdmin\n";
	powershell << "RunDefaultFunctions\n";
	
	powershell.close();
}

void SystemManager::Run(Settings* CSettings)
{
	LOG("Running SystemManager");
	std::string pathExe = Tools::GetCurrentExePath();
	std::string pathScript = Tools::RemoveExeFromPath(pathExe) + "\\powershell.ps1";
	std::string fullcmd = "start /wait powershell.exe -File \"" + pathScript + "\"";
	LOG("Starting powershell. Please wait for execution to finish...");
	system(fullcmd.c_str());
}