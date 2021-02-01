#include <iostream>

#include "proc/ProcessService.hpp"

int main()
{
    // Open process "re2.exe" with read/write permissions
    auto process {ProcessService::open("re2.exe", PROCESS_ALL_ACCESS)};

    int matildaAmmo = 0;
    int newMatildaAmmo = 12;

    // Get real address from virtual address and offsets (Thanks Cheat Engine !)
    auto pAmmo = process->getAddressFromOffsets(
        0x070A17E0,
        {0xC8, 0x6B8, 0x3E8, 0x100, 0x5C0, 0x800}
    );

    // Write the new matildaAmmo value
    process->write(pAmmo, &newMatildaAmmo, sizeof(newMatildaAmmo));

    // Read the matildaAmmo value
    process->read(pAmmo, &matildaAmmo, sizeof(matildaAmmo));

    std::cout << "Ammo : " << matildaAmmo << '\n';

    return 0;
}
