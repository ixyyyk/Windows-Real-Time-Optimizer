#include <iostream>
#include "Tools.h"
#include "System.h"
#include "Services.h"
#include "Processes.h"
#include "Log.h"
#include "PostChanges.h"
#include "Settings.h"

#define MODE_APPLY 1
#define MODE_RESUME 2
#define MODE_RESTORE 3

bool Apply();
bool Restart();
bool Resume();
bool Restore();

int main(int argc, char* argv[])
{
    if (!Tools::IsElevated())
    {
        ERRORLOG("Error: Admin rights not supplied. Quitting.");
        return false; 
    }
    DWORD MODE = 0; 
    bool bError = false;
    if (argc == 1) MODE = MODE_APPLY;
    else if (argc != 2)
    {
        ERRORLOG("Unknown parameters. Quitting");
        return 5;
    }
    else
    {
        if (*argv[1] == 'a') MODE = MODE_APPLY;
        else if (*argv[1] == 'r') MODE = MODE_RESUME;
        else if (*argv[1] == 'R') MODE = MODE_RESTORE;
    }

    switch (MODE)
    {
    case MODE_APPLY:
        LOG("MODE: Apply");
        if (!Apply())
        {
            ERRORLOG("Apply failed."); 
            bError = true;
        }
        
        break;
    case MODE_RESUME:
        LOG("MODE: Resume");
        if (!Restart())
        {
            ERRORLOG("Restart desktop failed.");
            bError = true;
        }
        if (!Resume())
        {
            ERRORLOG("Resume processes failed.");
            bError = true;
        }
        break;
    case MODE_RESTORE:
        LOG("MODE: Restore");
        if (!Restart())
        {
            ERRORLOG("Restart desktop failed.");
            bError = true;
        } 
        if (!Resume())
        {
            ERRORLOG("Resume processes failed.");
            bError = true;
        }
        if (!Restore())
        {
            ERRORLOG("Restore services failed.");
            bError = true;
        }
        break;
    default:
        ERRORLOG("Unknown parameters. Quitting");
        return 5;
    }
    return (int)bError;
}

bool Apply()
{
    Settings settings;
    Settings* CSettings = &settings;
    Log::Hello();
    LOG("Reading config from config.ini");

    if (!Tools::ReadConfig(CSettings))
    {
        ERRORLOG("Reading config failed. Quitting.");
        return false;
    }
    Log::InitConfig(CSettings->QUIET_OUTPUT);

    ProcessManager CProcessManager;
    ServiceManager CServiceManager;

    LOG("ServiceManager start");
    if (CSettings->CREATE_SERVICES_RESTORE_FILE)
    {
        CServiceManager.BackupServices(CSettings);
        LOG("CREATE_SERVICES_RESTORE_FILE is true. Making a backup configuration of services.");
    } 
    CServiceManager.ReadServices(CSettings);
    CServiceManager.StopServices(CSettings); 
    LOG("ServiceManager finished");

    LOG("ProcessManager start");
    CProcessManager.ReadProcesses(CSettings);
    CProcessManager.StopProcesses();
    if (CProcessManager.InitializeExportsWrap())
    {
        CProcessManager.FreezeProcesses();
    }
    else LOG("InitializeExports failed. Skipping FreezeProcesses");
    CProcessManager.LowerProcesses();
    CProcessManager.Clean(CSettings);
    LOG("ProcessManager finished");

    PostChangesHandler CPostChangesHandler;
    LOG("Running PostChangesHandler");
    CPostChangesHandler.Run(CSettings);
    LOG("PostChangesHandler finished");

    if (CSettings->RUN_OS_TWEAKS)
    {
        LOG("RUN_OS_TWEAKS = true, running SystemManager.");
        SystemManager CSystemManager;
        CSystemManager.Init(CSettings);
        CSystemManager.Run(CSettings);
    }
   
    if (CSettings->EXIT_AFTER_APPLYING)
    {
        LOG("EXIT_AFTER_APPLYING = True. Using ProcessManager to stop OptimizerGUI.");
        CProcessManager.ReadProcesses(CSettings);
        CProcessManager.StopProcesses();
    }
    Log::Goodbye();
    return true;
}

bool Restart()
{
    system("dwm.exe");
    system("explorer.exe");
    return true;
}

bool Resume()
{
    ProcessManager CProcessManager;
    if (!CProcessManager.InitializeExportsWrap())
    {
        LOG("InitializeExports failed. Cannot resume processes");
        return false;
    }
    if (!CProcessManager.ReadFreezedProcesses())
    {
        LOG("ReadFreezedProcesses failed. Cannot resume processes");
        return false;
    }
    CProcessManager.ResumeProcesses();
    return true;
}

bool Restore()
{
    ServiceManager CServiceManager;
    if (!CServiceManager.RestoreServices(false))
    {
        LOG("RestoreServices failed.");
        return false;
    }
    return true;
}
