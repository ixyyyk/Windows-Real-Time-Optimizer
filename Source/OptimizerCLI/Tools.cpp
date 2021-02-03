#define _CRT_SECURE_NO_WARNINGS
#include "Tools.h"
#include "Log.h"
#include "config/handler.h"
#include "Settings.h"
#include <WinBase.h>
#include <shlobj.h>
#include <winnls.h>
#include <shobjidl.h>
#include <objbase.h>
#include <objidl.h>
#include <shlguid.h>
#include <shobjidl_core.h>
#include <Windows.h>


std::wstring Tools::String2Wide(const std::string& str)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    return converterX.from_bytes(str);
}

inline std::wstring Tools::convertNarrowToWideStringEx(const std::string& as)
{
    if (as.empty())    return std::wstring();
    size_t reqLength = ::MultiByteToWideChar(CP_ACP, 0, as.c_str(), (int)as.length(), 0, 0);
    std::wstring ret(reqLength, L'\0');
    ::MultiByteToWideChar(CP_ACP, 0, as.c_str(), (int)as.length(), &ret[0], (int)ret.length());
    return ret;
}

std::string Tools::Wide2String(const std::wstring& wstr)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    return converterX.to_bytes(wstr);
}

HRESULT Tools::CreateShortcut(std::string pszTargetfile, std::string pszLinkfile, std::string pszCurdir)
{
    HRESULT         hRes;                  
    IShellLink*     pShellLink;            
    IPersistFile*   pPersistFile;      

    CoInitialize(NULL);
    hRes = E_INVALIDARG;
    std::wstring wTargetFile = convertNarrowToWideStringEx(pszTargetfile);
    std::wstring wLinkfile = convertNarrowToWideStringEx(pszLinkfile);
    std::wstring wCurdir = convertNarrowToWideStringEx(pszCurdir);
    if ((!wTargetFile.empty()) && (!wLinkfile.empty()) && (!wCurdir.empty()))
    {
        hRes = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&pShellLink);       
        if (SUCCEEDED(hRes))
        {
            hRes = pShellLink->SetPath(wTargetFile.c_str());
            hRes = pShellLink->SetWorkingDirectory(wCurdir.c_str());
            hRes = pShellLink->QueryInterface(IID_IPersistFile, (LPVOID*)&pPersistFile);
            if (SUCCEEDED(hRes))
            {
                hRes = pPersistFile->Save(wLinkfile.c_str(), TRUE);
                pPersistFile->Release();
            }
            pShellLink->Release();
        }
    }
    CoUninitialize();
    return (hRes);
}

std::string Tools::GetCurrentExePath()
{
    char Path[MAX_PATH];
    GetModuleFileNameA(NULL, Path, sizeof(Path));
    std::string sPath = Path;
    return sPath;
}


std::string Tools::RemoveExeFromPath(std::string Path)
{
    std::string::size_type pos = std::string(Path).find_last_of("\\/");
    return std::string(Path).substr(0, pos);
}

BOOL Tools::StartProcess(std::string Path, DWORD priority)
{
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    std::string startingDirectory = Tools::RemoveExeFromPath(Path);
    BOOL result = CreateProcessA
    (
        Path.c_str(),   
        NULL,              
        NULL,                  
        NULL,                   
        FALSE,                 
        priority | DETACHED_PROCESS,     
        NULL,           
        startingDirectory.c_str(),          
        &si,           
        &pi    
    );
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return result;
}

BOOL Tools::IsElevated()
{
    BOOL fRet = FALSE;
    HANDLE hToken = NULL;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
    {
        TOKEN_ELEVATION Elevation;
        DWORD cbSize = sizeof(TOKEN_ELEVATION);
        if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize))
        {
            fRet = Elevation.TokenIsElevated;
        }
    }
    if (hToken)
    {
        CloseHandle(hToken);
    }
    return fRet;
}

const char* Tools::currentTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t curTime = std::chrono::system_clock::to_time_t(now);
    return std::ctime(&curTime);
}

std::string Tools::GetStartupFolderPath()
{
    PWSTR pszPath;
    HRESULT hr = SHGetKnownFolderPath(FOLDERID_Startup,
        0,    
        NULL,  
        &pszPath);
    if (SUCCEEDED(hr))
    {
        std::wstring path(pszPath);
        CoTaskMemFree(static_cast<LPVOID>(pszPath));
        return Tools::Wide2String(path);
    }
    std::string error = "";
    return error;
}


bool Tools::ReadConfig(Settings* CSettings)
{
    std::string CurExePath = Tools::GetCurrentExePath();
    std::string DirectoryPath = Tools::RemoveExeFromPath(CurExePath);
    std::string ConfigPath = DirectoryPath + "\\config.ini";
    config::Handler handler;
    try
    {
        handler.Load(ConfigPath, {});
    }
    catch (...)
    {
        LOG("Error while loading config.ini, possibly file missing? Quitting.");
        return false;
    }
    config::Item* setting;
    
    //[SERVICES]
    setting = handler.Get("SERVICES.DISABLE_ALL_INTERNET");
    if (setting != NULL)
    {
        try
        {
            CSettings->DISABLE_ALL_INTERNET = setting->GetBoolean();
        }
        catch (std::runtime_error)
        {
            std::string value = "value";
            if (setting->GetValueType() == config::ValueType::STRING)
            { 
                value = setting->GetString();
            }
            ERRORLOG("Cannot interpret " + value + " as bool. Using safe default. Setting: SERVICES.DISABLE_ALL_INTERNET");
        }
    }
    else 
    {
        ERRORLOG("SERVICES.DISABLE_ALL_INTERNET not found. Using safe default.");
    }
    
    setting = handler.Get("SERVICES.DISABLE_WIRELESS_INTERNET");
    if (setting != NULL){try{ CSettings->DISABLE_WIRELESS_INTERNET = setting->GetBoolean();}
        catch (std::runtime_error){
            std::string value = "value";
            if (setting->GetValueType() == config::ValueType::STRING) value = setting->GetString();
            ERRORLOG("Cannot interpret " + value + " as bool. Using safe default. Setting: SERVICES.DISABLE_WIRELESS_INTERNET");}
    } else ERRORLOG("SERVICES.DISABLE_WIRELESS_INTERNET not found. Using safe default.");
    
    setting = handler.Get("SERVICES.DISABLE_BLUETOOTH");
    if (setting != NULL)
    {
        try
        {
            CSettings->DISABLE_BLUETOOTH = setting->GetBoolean();
        }
        catch (std::runtime_error)
        {
            std::string value = "value";
            if (setting->GetValueType() == config::ValueType::STRING)
            {
                value = setting->GetString();
            }
            ERRORLOG("Cannot interpret " + value + " as bool. Using safe default. Setting: SERVICES.DISABLE_BLUETOOTH");
        }
    }
    else
    {
        ERRORLOG("SERVICES.DISABLE_BLUETOOTH not found. Using safe default.");
    }


    setting = handler.Get("SERVICES.DISABLE_AUDIO");
    if (setting != NULL)
    {
        try
        {
            CSettings->DISABLE_AUDIO = setting->GetBoolean();
        }
        catch (std::runtime_error)
        {
            std::string value = "value";
            if (setting->GetValueType() == config::ValueType::STRING)
            {
                value = setting->GetString();
            }
            ERRORLOG("Cannot interpret " + value + " as bool. Using safe default. Setting: SERVICES.DISABLE_AUDIO");
        }
    }
    else
    {
        ERRORLOG("SERVICES.DISABLE_AUDIO not found. Using safe default.");
    }


    //[OS] 
    setting = handler.Get("OS.RUN_OS_TWEAKS");
    if (setting != NULL)
    {
        try
        {
            CSettings->RUN_OS_TWEAKS = setting->GetBoolean();
        }
        catch (std::runtime_error)
        {
            std::string value = "value";
            if (setting->GetValueType() == config::ValueType::STRING)
            {
                value = setting->GetString();
            }
            ERRORLOG("Cannot interpret " + value + " as bool. Using safe default. Setting: OS.RUN_OS_TWEAKS");
        }
    }
    else
    {
        ERRORLOG("OS.RUN_OS_TWEAKS not found. Using safe default.");
    }


    setting = handler.Get("OS.TURN_OFF_WINDOWS_DEFENDER");
    if (setting != NULL)
    {
        try
        {
            CSettings->TURN_OFF_WINDOWS_DEFENDER = setting->GetBoolean();
        }
        catch (std::runtime_error)
        {
            std::string value = "value";
            if (setting->GetValueType() == config::ValueType::STRING)
            {
                value = setting->GetString();
            }
            ERRORLOG("Cannot interpret " + value + " as bool. Using safe default. Setting: OS.TURN_OFF_WINDOWS_DEFENDER");
        }
    }
    else
    {
        ERRORLOG("OS.TURN_OFF_WINDOWS_DEFENDER not found. Using safe default.");
    }


    setting = handler.Get("OS.TURN_OFF_WINDOWS_FIREWALL");
    if (setting != NULL)
    {
        try
        {
            CSettings->TURN_OFF_WINDOWS_FIREWALL = setting->GetBoolean();
        }
        catch (std::runtime_error)
        {
            std::string value = "value";
            if (setting->GetValueType() == config::ValueType::STRING)
            {
                value = setting->GetString();
            }
            ERRORLOG("Cannot interpret " + value + " as bool. Using safe default. Setting: OS.TURN_OFF_WINDOWS_FIREWALL");
        }
    }
    else
    {
        ERRORLOG("OS.TURN_OFF_WINDOWS_FIREWALL not found. Using safe default.");
    }


    setting = handler.Get("OS.UNINSTALL_DEFAULT_WINDOWS_APPS");
    if (setting != NULL)
    {
        try
        {
            CSettings->UNINSTALL_DEFAULT_WINDOWS_APPS = setting->GetBoolean();
        }
        catch (std::runtime_error)
        {
            std::string value = "value";
            if (setting->GetValueType() == config::ValueType::STRING)
            {
                value = setting->GetString();
            }
            ERRORLOG("Cannot interpret " + value + " as bool. Using safe default. Setting: OS.UNINSTALL_DEFAULT_WINDOWS_APPS");
        }
    }
    else
    {
        ERRORLOG("OS.UNINSTALL_DEFAULT_WINDOWS_APPS not found. Using safe default.");
    }

    //[SETTINGS]
    setting = handler.Get("SETTINGS.NO_PERMANENT_CHANGES");
    if (setting != NULL)
    {
        try
        {
            CSettings->NO_PERMANENT_CHANGES = setting->GetBoolean();
        }
        catch (std::runtime_error)
        {
            std::string value = "value";
            if (setting->GetValueType() == config::ValueType::STRING)
            {
                value = setting->GetString();
            }
            ERRORLOG("Cannot interpret " + value + " as bool. Using safe default. Setting: SETTINGS.NO_PERMANENT_CHANGES");
        }
    }
    else
    {
        ERRORLOG("SETTINGS.NO_PERMANENT_CHANGES not found. Using safe default.");
    }


    setting = handler.Get("SETTINGS.CREATE_SERVICES_RESTORE_FILE");
    if (setting != NULL)
    {
        try
        {
            CSettings->CREATE_SERVICES_RESTORE_FILE = setting->GetBoolean();
        }
        catch (std::runtime_error)
        {
            std::string value = "value";
            if (setting->GetValueType() == config::ValueType::STRING)
            {
                value = setting->GetString();
            }
            ERRORLOG("Cannot interpret " + value + " as bool. Using safe default. Setting: SETTINGS.CREATE_SERVICES_RESTORE_FILE");
        }
    }
    else
    {
        ERRORLOG("SETTINGS.CREATE_SERVICES_RESTORE_FILE not found. Using safe default.");
    }


    setting = handler.Get("SETTINGS.AUTO_APPLY_CONFIG");
    if (setting != NULL)
    {
        try
        {
            CSettings->AUTO_APPLY_CONFIG = setting->GetBoolean();
        }
        catch (std::runtime_error)
        {
            std::string value = "value";
            if (setting->GetValueType() == config::ValueType::STRING)
            {
                value = setting->GetString();
            }
            ERRORLOG("Cannot interpret " + value + " as bool. Using safe default. Setting: SETTINGS.AUTO_APPLY_CONFIG");
        }
    }
    else
    {
        ERRORLOG("SETTINGS.AUTO_APPLY_CONFIG not found. Using safe default.");
    }


    setting = handler.Get("SETTINGS.AUTO_START_GUI");
    if (setting != NULL)
    {
        try
        {
            CSettings->AUTO_START_GUI = setting->GetBoolean();
        }
        catch (std::runtime_error)
        {
            std::string value = "value";
            if (setting->GetValueType() == config::ValueType::STRING)
            {
                value = setting->GetString();
            }
            ERRORLOG("Cannot interpret " + value + " as bool. Using safe default. Setting: SETTINGS.AUTO_START_GUI");
        }
    }
    else
    {
        ERRORLOG("SETTINGS.AUTO_START_GUI not found. Using safe default.");
    }


    setting = handler.Get("SETTINGS.QUIET_OUTPUT");
    if (setting != NULL)
    {
        try
        {
            CSettings->QUIET_OUTPUT = setting->GetBoolean();
        }
        catch (std::runtime_error)
        {
            std::string value = "value";
            if (setting->GetValueType() == config::ValueType::STRING)
            {
                value = setting->GetString();
            }
            ERRORLOG("Cannot interpret " + value + " as bool. Using safe default. Setting: SETTINGS.QUIET_OUTPUT");
        }
    }
    else
    {
        ERRORLOG("SETTINGS.QUIET_OUTPUT not found. Using safe default.");
    }


    setting = handler.Get("SETTINGS.EXIT_AFTER_APPLYING");
    if (setting != NULL)
    {
        try
        {
            CSettings->EXIT_AFTER_APPLYING = setting->GetBoolean();
        }
        catch (std::runtime_error)
        {
            std::string value = "value";
            if (setting->GetValueType() == config::ValueType::STRING)
            {
                value = setting->GetString();
            }
            ERRORLOG("Cannot interpret " + value + " as bool. Using safe default. Setting: SETTINGS.EXIT_AFTER_APPLYING");
        }
    }
    else
    {
        ERRORLOG("SETTINGS.EXIT_AFTER_APPLYING not found. Using safe default.");
    }

    //[PROCESSES]
    setting = handler.Get("PROCESSES.DISABLE_DESKTOP_ENVIRONMENT");
    if (setting != NULL)
    {
        try
        {
            CSettings->DISABLE_DESKTOP_ENVIRONMENT = setting->GetBoolean();
        }
        catch (std::runtime_error)
        {
            std::string value = "value";
            if (setting->GetValueType() == config::ValueType::STRING)
            {
                value = setting->GetString();
            }
            ERRORLOG("Cannot interpret " + value + " as bool. Using safe default. Setting: PROCESSES.DISABLE_DESKTOP_ENVIRONMENT");
        }
    }
    else
    {
        ERRORLOG("PROCESSES.DISABLE_DESKTOP_ENVIRONMENT not found. Using safe default.");
    }


    setting = handler.Get("PROCESSES.LOWER_NON_CRITICAL_PROCESSES");
    if (setting != NULL)
    {
        try
        {
            CSettings->LOWER_NON_CRITICAL_PROCESSES = setting->GetBoolean();
        }
        catch (std::runtime_error)
        {
            std::string value = "value";
            if (setting->GetValueType() == config::ValueType::STRING)
            {
                value = setting->GetString();
            }
            ERRORLOG("Cannot interpret " + value + " as bool. Using safe default. Setting: PROCESSES.LOWER_NON_CRITICAL_PROCESSES");
        }
    }
    else
    {
        ERRORLOG("PROCESSES.LOWER_NON_CRITICAL_PROCESSES not found. Using safe default.");
    }

    //[PROCESSES_LIST]
    std::unordered_map<std::string, config::Item>* sectionMap = handler.GetSection("PROCESSES_LIST");
    if (sectionMap == NULL)
    {
        ERRORLOG("Error while parsing PROCESSES_LIST. Skipping.");
    }
    else
    {
        for (auto kv : *sectionMap)
        {
            if (kv.second.GetString() == "STOP") CSettings->stopList.push_back(kv.first);
            else if (kv.second.GetString() == "FREEZE") CSettings->freezeList.push_back(kv.first);
            else if (kv.second.GetString() == "LOWER") CSettings->lowerList.push_back(kv.first);
        }
    }
    
    //[START_LIST]
    std::unordered_map<std::string, config::Item>* sectionMap2 = handler.GetSection("AUTORUN");
    if (sectionMap2 == NULL)
    {
        //ERRORLOG("Error while parsing AUTORUN. Skipping.");
    }
    else 
    {
        for (auto kv : *sectionMap2)
        {
            DWORD priority = NORMAL_PRIORITY_CLASS;
            if (kv.second.GetString() == "BELOW_NORMAL") priority = BELOW_NORMAL_PRIORITY_CLASS;
            else if (kv.second.GetString() == "ABOVE_NORMAL") priority = ABOVE_NORMAL_PRIORITY_CLASS;
            else if (kv.second.GetString() == "HIGH") priority = HIGH_PRIORITY_CLASS;
            std::pair<std::string, DWORD> newpair;
            newpair.first = kv.first;
            newpair.second = priority;
            CSettings->startList.push_back(newpair);
        }
    }
    return true;
}