#include "PostChanges.h"
#include "Tools.h"
#include "Log.h"

void PostChangesHandler::Run(Settings* CSettings)
{
	if (CSettings->AUTO_APPLY_CONFIG)
	{
		LOG("AUTO_APPLY_CONFIG = True. Adding OptimizerApply shortcut to FOLDERID_Startup");
		std::string ExePath = Tools::GetCurrentExePath();
		std::string RemovedExe = Tools::RemoveExeFromPath(ExePath);
		std::string StartupFolderPath = Tools::GetStartupFolderPath();
		StartupFolderPath += "\\OptimizerApply.lnk";
		LOG("CreateShortcut: ExePath = " + ExePath + " LinkFile = " + StartupFolderPath + " CurDir = " + RemovedExe);
		HRESULT result = Tools::CreateShortcut(ExePath.c_str(), StartupFolderPath.c_str(), RemovedExe.c_str());
		if (SUCCEEDED(result)) LOG("CreateShortcut succeeded");
		else LOG("CreateShortcut failed");
	}
	if (CSettings->AUTO_START_GUI)
	{
		LOG("AUTO_APPLY_CONFIG = True. Adding OptimizerGUI shortcut to FOLDERID_Startup");
		std::string ExePath = Tools::GetCurrentExePath();
		std::string RemovedExe = Tools::RemoveExeFromPath(ExePath);
		std::string GUIPath = RemovedExe + "\\OptimizerGUI.exe";
		std::string StartupFolderPath = Tools::GetStartupFolderPath();
		StartupFolderPath += "\\OptimizerGUI.lnk";
		LOG("CreateShortcut: ExePath = " + GUIPath + " LinkFile = " + StartupFolderPath + " CurDir = " + RemovedExe);
		HRESULT result = Tools::CreateShortcut(GUIPath, StartupFolderPath, RemovedExe);
		if (SUCCEEDED(result)) LOG("CreateShortcut succeeded");
		else LOG("CreateShortcut failed");
	}
	if (!CSettings->startList.empty())
	{
		LOG("startList is not empty. Starting processes");
		for (auto& pair : CSettings->startList)
		{
			DWORD priority = pair.second;
			LOG("Starting " + pair.first + " with priority " + std::to_string(priority));
			BOOL result = Tools::StartProcess(pair.first, priority);
			if (result) LOG("StartProcess succeeded.");
			else LOG("StartProcess failed.");
		}
	}
	else LOG("startList is empty.");
}
