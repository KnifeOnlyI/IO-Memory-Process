#include "proc/Process.hpp"

#include <iostream>
#include <utility>

Process::Process(std::string name, HANDLE handle, uintptr_t address)
    : _name {std::move(name)}, _handle {handle}, _address {address}
{
}

DWORD_PTR Process::getAddressFromOffsets(DWORD_PTR virtualAddress, const std::vector<unsigned int> &offsets) const
{
    DWORD_PTR addr {_address + virtualAddress};

    std::cout << "\"" << _name << "\"(" << std::hex << _address << ") + " << std::hex << virtualAddress;

    ReadProcessMemory(_handle, (DWORD_PTR *) addr, &addr, sizeof(addr), nullptr);

    std::cout << " -> " << std::hex << addr << '\n';

    for (int i {0}; i < offsets.size(); i++)
    {
        std::cout << "[" << std::hex << addr << " + " << offsets[i] << "]";

        // Add offset to address to find the next pointer
        addr += offsets[i];

        if (i != offsets.size() - 1)
        {
            // Find which address is pointed by *addr pointer
            ReadProcessMemory(_handle, (DWORD_PTR *) addr, &addr, sizeof(addr), nullptr);
            std::cout << " -> " << std::hex << addr << '\n';
        }
        else
        {
            std::cout << " = " << std::hex << addr << '\n';
        }
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
