//https://ntopcode.wordpress.com/tag/ntsuspendprocess/

#pragma once
#include <Windows.h>

#define STATUS_INSUFFICIENT_RESOURCES 0xC000009A

typedef _Return_type_success_(return >= 0) LONG NTSTATUS;
typedef NTSTATUS* PNTSTATUS;

#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

typedef NTSTATUS(NTAPI* pNtSuspendProcess)(HANDLE ProcessHandle);

pNtSuspendProcess fNtSuspendProcess;

typedef NTSTATUS(NTAPI* pNtResumeProcess)(HANDLE ProcessHandle);

pNtResumeProcess fNtResumeProcess;

BOOLEAN InitializeExports()
{
    HMODULE hNtdll = GetModuleHandle(L"NTDLL");

    if (!hNtdll)
    {
        return FALSE;
    }

    fNtSuspendProcess = (pNtSuspendProcess)GetProcAddress(hNtdll, "NtSuspendProcess");

    fNtResumeProcess = (pNtResumeProcess)GetProcAddress(hNtdll, "NtResumeProcess");

    if (!fNtResumeProcess || !fNtSuspendProcess)
    {
        return FALSE;
    }

    return TRUE;
}

NTSTATUS NTAPI NtSuspendProcess(HANDLE ProcessHandle)
{
    if (!fNtSuspendProcess)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    return fNtSuspendProcess(ProcessHandle);
}

BOOLEAN WINAPI SuspendProcess(HANDLE ProcessHandle)
{
    if (!ProcessHandle)
    {
        return FALSE;
    }

    return (NT_SUCCESS(NtSuspendProcess(ProcessHandle))) ? TRUE : FALSE;
}

NTSTATUS NTAPI NtResumeProcess(HANDLE ProcessHandle)
{
    if (!fNtResumeProcess)
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    return fNtResumeProcess(ProcessHandle);
}

BOOLEAN WINAPI ResumeProcess(HANDLE ProcessHandle)
{
    if (!ProcessHandle)
    {
        return FALSE;
    }

    return (NT_SUCCESS(NtResumeProcess(ProcessHandle))) ? TRUE : FALSE;
}