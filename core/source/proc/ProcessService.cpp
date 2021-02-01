#include "proc/ProcessService.hpp"

#include <TlHelp32.h>
#include <iostream>

std::shared_ptr<Process> ProcessService::open(const std::string &name, DWORD access)
{
    DWORD_PTR procId {getProcID(name)};

    if (procId == 0)
    {
        throw std::exception("Error when get process ID");
    }

    DWORD_PTR moduleBase {getModuleBaseAddress(procId, name)};

    if (moduleBase == 0)
    {
        throw std::exception("Error when get module base address");
    }

    HANDLE handle {OpenProcess(access, NULL, procId)};

    return std::make_shared<Process>(name, handle, moduleBase);
}

DWORD_PTR ProcessService::getProcID(const std::string &name)
{
    DWORD_PTR procId {0};
    HANDLE hSnap {CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)};

    if (hSnap != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);

        if (Process32First(hSnap, &procEntry))
        {
            do
            {
                const std::string curProcessName {procEntry.szExeFile};

                if (name == curProcessName)
                {
                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));

        }
    }

    CloseHandle(hSnap);

    return procId;
}

DWORD_PTR ProcessService::getModuleBaseAddress(DWORD_PTR pid, const std::string &name)
{
    DWORD_PTR modBaseAddr {0};
    HANDLE hSnap {CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid)};

    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);

        if (Module32First(hSnap, &modEntry))
        {
            do
            {
                const std::string curModuleName {modEntry.szModule};

                if (name == curModuleName)
                {
                    modBaseAddr = reinterpret_cast<DWORD_PTR>(modEntry.modBaseAddr);

                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }

    CloseHandle(hSnap);

    return modBaseAddr;
}

bool ProcessService::exists(const std::string &name)
{
    return getProcID(name) != 0;
}
