#include "proc/Process.hpp"

Process::Process(HANDLE handle, uintptr_t address)
    : _handle {handle}, _address {address}
{
}

uintptr_t Process::getAddressFromOffsets(uintptr_t virtualAddress, const std::vector<unsigned int> &offsets) const
{
    uintptr_t addr {_address + virtualAddress};

    for (unsigned int offset : offsets)
    {
        ReadProcessMemory(_handle, (BYTE *) addr, &addr, sizeof(addr), nullptr);

        addr += offset;
    }

    return addr;
}

void Process::read(uintptr_t address, void *buffer, size_t size) const
{
    ReadProcessMemory(_handle, (BYTE *) address, buffer, size, nullptr);
}

void Process::write(uintptr_t address, void *buffer, size_t size) const
{
    WriteProcessMemory(_handle, (BYTE *) address, buffer, size, nullptr);
}
