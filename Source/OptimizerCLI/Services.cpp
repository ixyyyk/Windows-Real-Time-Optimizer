#include "Services.h"
#include <iostream>
#include "Tools.h"
#include "Log.h"

bool ServiceManager::ReadServices(Settings* CSettings)
{
	LOG("Reading services from services.txt");
	std::string Directory = Tools::RemoveExeFromPath(Tools::GetCurrentExePath());
	std::ifstream input(Directory + "\\services.txt");
	if (input.fail())
	{
		ERRORLOG("services.txt not found.");
		return false;
	}
	std::vector<std::string>* curType = nullptr;
	for (std::string line; getline(input, line); )
	{
		if (line.empty()) continue;
		if (line.at(0) == '[')
		{
			if (line.compare("[DISABLED]") == 0)
			{
				LOG("[DISABLED] hit. Changing curType to ServicesToStopDisabled.");
				curType = &ServicesToStopDisabled;
			}
			else if (line.compare("[MANUAL]") == 0)
			{
				LOG("[MANUAL] hit. Changing curType to ServicesToStopManual.");
				curType = &ServicesToStopManual;
			}
			else if (line.compare("[INTERNET]") == 0)
			{
				if (CSettings->DISABLE_ALL_INTERNET == true)
				{
					LOG("[INTERNET] hit and DISABLE_ALL_INTERNET = True. Changing curType to ServicesToStopDisabled.");
					curType = &ServicesToStopDisabled;
				}
				else
				{
					LOG("[INTERNET] hit but DISABLE_ALL_INTERNET = False. Changing curType to nullptr.");
					curType = nullptr;
				}		
			}
			else if (line.compare("[WIRELESS]") == 0)
			{
				if (CSettings->DISABLE_WIRELESS_INTERNET == true)
				{
					LOG("[WIRELESS] hit and DISABLE_WIRELESS_INTERNET = True. Changing curType to ServicesToStopDisabled.");
					curType = &ServicesToStopDisabled;
				}
				else
				{
					LOG("[WIRELESS] hit but DISABLE_WIRELESS_INTERNET = False. Changing curType to nullptr.");
					curType = nullptr;
				}
			}
			else if (line.compare("[BLUETOOTH]") == 0)
			{
				if (CSettings->DISABLE_BLUETOOTH == true)
				{
					LOG("[BLUETOOTH] hit and DISABLE_BLUETOOTH = True. Changing curType to ServicesToStopDisabled.");
					curType = &ServicesToStopDisabled;
				}
				else
				{
					LOG("[BLUETOOTH] hit but DISABLE_BLUETOOTH = False. Changing curType to nullptr.");
					curType = nullptr;
				}
			}
			else if (line.compare("[NOTEBOOK]") == 0)
			{
				if (CSettings->USING_NOTEBOOK == false)
				{
					LOG("[NOTEBOOK] hit and USING_NOTEBOOK = False. Changing curType to ServicesToStopDisabled.");
					curType = &ServicesToStopDisabled;
				}
				else
				{
					LOG("[NOTEBOOK] hit but USING_NOTEBOOK = True. Changing curType to nullptr.");
					curType = nullptr;
				}
			}
			else if (line.compare("[AUDIO]") == 0)
			{
				if (CSettings->DISABLE_AUDIO == true)
				{
					LOG("[AUDIO] hit and DISABLE_AUDIO = True. Changing curType to ServicesToStopDisabled.");
					curType = &ServicesToStopDisabled;
				}
				else
				{
					LOG("[AUDIO] hit but DISABLE_AUDIO = False. Changing curType to nullptr.");
					curType = nullptr;
				}
			}
		}
		else if (curType != nullptr)
		{
			LOG("Adding service: " + line);
			curType->push_back(line);
		}
	}
	return true;
}

void ServiceManager::StopServices(Settings* CSettings)
{
	LOG("Stopping services to Disabled");
	for (auto& Service : ServicesToStopDisabled)
	{		
		LOG("Current service: " + Service);
		if (Service.find('_') != std::string::npos)
		{
			LOG("Service name is dynamic, using wmic");
			std::string name = "\"" + Service + "%\"";
			if (CSettings->NO_PERMANENT_CHANGES == false)
			{
				LOG("NO_PERMANENT_CHANGES = False. Changing mode to disabled.");
				std::string cmd = "wmic service where 'name like " + name + "' call ChangeStartmode Disabled";
				if (CSettings->QUIET_OUTPUT) cmd += " >nul 2>&1";
				LOG("Using command: " + cmd);
				system(cmd.c_str());
			}		
			std::string cmd = "wmic service where 'name like " + name + "' call stopservice";
			if (CSettings->QUIET_OUTPUT) cmd += " >nul 2>&1";
			LOG("Stopping service with command: " + cmd);
			system(cmd.c_str());
		}
		else
		{
			LOG("Service name is not dynamic, using NET and SC");
			if (CSettings->NO_PERMANENT_CHANGES == false)
			{
				LOG("NO_PERMANENT_CHANGES = False. Changing mode to disabled.");
				std::string cmd = "SC config " + Service + " start= disabled";
				if (CSettings->QUIET_OUTPUT) cmd += " >nul 2>&1";
				LOG("Using command: " + cmd);
				system(cmd.c_str());
			}
			std::string cmd = "NET STOP " + Service + " /y";
			if (CSettings->QUIET_OUTPUT) cmd += " >nul 2>&1";
			LOG("Stopping service with command: " + cmd);
			system(cmd.c_str());
		}
	}

	LOG("Stopping services to Manual");
	for (auto& Service : ServicesToStopManual)
	{
		LOG("Current service: " + Service);
		if (Service.find('_') != std::string::npos)
		{	
			LOG("Service name is dynamic, using wmic");
			std::string name = "\"" + Service + "%\"";
			if (CSettings->NO_PERMANENT_CHANGES == false)
			{
				LOG("NO_PERMANENT_CHANGES = False. Changing mode to manual.");
				std::string cmd = "wmic service where 'name like " + name + "' call ChangeStartmode Manual";
				if (CSettings->QUIET_OUTPUT) cmd += " >nul 2>&1";
				LOG("Using command: " + cmd);
				system(cmd.c_str());
			}
			std::string cmd = "wmic service where 'name like " + name + "' call stopservice";
			if (CSettings->QUIET_OUTPUT) cmd += " >nul 2>&1";
			LOG("Stopping service with command: " + cmd);
			system(cmd.c_str());
		}
		else
		{
			LOG("Service name is not dynamic, using NET and SC");
			if (CSettings->NO_PERMANENT_CHANGES == false)
			{
				LOG("NO_PERMANENT_CHANGES = False. Changing mode to manual.");
				std::string cmd = "SC config " + Service + " start= demand";
				if (CSettings->QUIET_OUTPUT) cmd += " >nul 2>&1";
				LOG("Using command: " + cmd);
				system(cmd.c_str());
			}
			std::string cmd = "NET STOP " + Service + " /y"; 
			if (CSettings->QUIET_OUTPUT) cmd += " >nul 2>&1";
			LOG("Stopping service with command: " + cmd);
			system(cmd.c_str());
		}
	}
}

bool ServiceManager::BackupServices(Settings* CSettings)
{
	std::string command = "wmic service get Name, Startmode /format:list >";
	std::string absolutepath = Tools::RemoveExeFromPath(Tools::GetCurrentExePath());
	absolutepath += "\\restoration.txt";
	command += " \"" + absolutepath + "\"";
	LOG("Attempting to backup all services with command: " + command);
	system(command.c_str());
	return true;
}

bool ServiceManager::RestoreServices(bool quiet)
{
	std::ifstream restoration;
	std::string path = Tools::RemoveExeFromPath(Tools::GetCurrentExePath());
	path += "\\restoration.txt";
	restoration.open(path);
	if (restoration.fail())
	{
		ERRORLOG("Cannot open restoration.txt");
		return false;
	}
	std::string line;
	char name[] = "Name=";
	char mode[] = "StartMode";
	std::string lastService = "";
	std::string modeManual = "StartMode=Manual";
	std::string modeAuto = "StartMode=Auto";
	while (getline(restoration, line))
	{
		if (line.length() < 2) continue;
		if (strncmp(name, line.c_str(), strlen(name)) == 0)
		{
			lastService = line.substr((line.find_first_of('=')));
			LOG("Read service name as " + lastService + " from line " + line);
			continue;
		}
		if (line.compare(modeManual) == 0)
		{
			ServicesToRestoreManual.push_back(lastService);
			LOG("Adding service " + lastService + " to Manual based on line " + line);
		}
		else if (line.compare(modeAuto) == 0)
		{
			ServicesToRestoreAutomatic.push_back(lastService);
			LOG("Adding service " + lastService + " to Automatic based on line " + line);
		}
	}
	
	
	for (auto& service : ServicesToRestoreAutomatic)
	{
		LOG("Current service: " + service);
		size_t usPos = service.find('_');
		if (usPos != std::string::npos)
		{
			LOG("Service name is dynamic, stripping characters after '_'");
			std::string name = "\"" + service.substr(usPos+1) + "%\"";
			std::string cmd = "wmic service where 'name like " + name + "' call ChangeStartmode Automatic";
			if (quiet) cmd += " >nul 2>&1";
			LOG("Changing startmode to Automatic with command: " + cmd);
			system(cmd.c_str());
			cmd = "wmic service where 'name like " + name + "' call startservice";
			if (quiet) cmd += " >nul 2>&1";
			LOG("Starting service with command: " + cmd);
			system(cmd.c_str());
		}
		else
		{
			LOG("Service name is not dynamic, using full name.");
			LOG("NO_PERMANENT_CHANGES = False. Changing mode to disabled.");
			std::string cmd = "wmic service where 'name= " + service + "' call ChangeStartmode Automatic";
			if (quiet) cmd += " >nul 2>&1";
			LOG("Using command: " + cmd);
			system(cmd.c_str());
			cmd = "SC START " + service + " /y";
			if (quiet) cmd += " >nul 2>&1";
			LOG("Starting service with command: " + cmd);
			system(cmd.c_str());
		}
	}

	for (auto& service : ServicesToRestoreManual)
	{
		LOG("Current service: " + service);
		size_t usPos = service.find('_');
		if (usPos != std::string::npos)
		{
			LOG("Service name is dynamic, stripping characters after '_'");
			std::string name = "\"" + service.substr(usPos + 1) + "%\"";
			std::string cmd = "wmic service where 'name like " + name + "' call ChangeStartmode Manual";
			if (quiet) cmd += " >nul 2>&1";
			LOG("Changing startmode to Automatic with command: " + cmd);
			system(cmd.c_str());
			cmd = "wmic service where 'name like " + name + "' call startservice";
			if (quiet) cmd += " >nul 2>&1";
			LOG("Starting service with command: " + cmd);
			system(cmd.c_str());
		}
		else
		{
			LOG("Service name is not dynamic, using full name.");
			LOG("NO_PERMANENT_CHANGES = False. Changing mode to disabled.");
			std::string cmd = "wmic service where 'name= " + service + "' call ChangeStartmode Manual";
			if (quiet) cmd += " >nul 2>&1";
			LOG("Using command: " + cmd);
			system(cmd.c_str());
			cmd = "SC START " + service + " /y";
			if (quiet) cmd += " >nul 2>&1";
			LOG("Starting service with command: " + cmd);
			system(cmd.c_str());
		}
	}
	return true;
}
