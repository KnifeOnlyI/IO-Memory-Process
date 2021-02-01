#include "proc/Process.hpp"

#include <iostream>

Process::Process(HANDLE handle, uintptr_t address)
    : _handle {handle}, _address {address}
{
}

DWORD_PTR Process::getAddressFromOffsets(DWORD_PTR virtualAddress, const std::vector<unsigned int> &offsets) const
{
    // _address = 0x400000
    // _virtualAddress = 0x1100F8
    DWORD_PTR addr {_address + virtualAddress}; // Results = 0x5100f8

    int i {0};

    for (unsigned int offset : offsets)
    {
        if (i == 0)
        {
            std::cout << "\"ac_client.exe\" + " << std::hex << virtualAddress;
        }
        else
        {
            std::cout << "[" << std::hex << addr << " + " << offset << "]";
        }

        // Find which address is pointed by *addr pointer
        ReadProcessMemory(_handle, (DWORD_PTR *) addr, &addr, sizeof(addr), nullptr);

        std::cout << " -> " << std::hex << addr << '\n';

        // Add offset to address to find the next pointer
        addr += offset;

        i++;
    }

    return addr;
}

void Process::read(DWORD_PTR address, void *buffer, size_t size) const
{
    ReadProcessMemory(_handle, (DWORD_PTR *) address, buffer, size, nullptr);
}

void Process::write(DWORD_PTR address, void *buffer, size_t size) const
{
    WriteProcessMemory(_handle, (DWORD_PTR *) address, buffer, size, nullptr);
}
