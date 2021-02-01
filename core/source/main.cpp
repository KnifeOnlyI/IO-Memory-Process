#include <iostream>

#include "proc/ProcessService.hpp"
#include "game/EquipedWeapon.hpp"

int main()
{
    // Open process "re2.exe" with read/write permissions
    //auto process {ProcessService::open("re2.exe", PROCESS_ALL_ACCESS)};
    auto process {ProcessService::open("ac_client.exe", PROCESS_ALL_ACCESS)};
    auto equipedWeapon {new EquipedWeapon(process)};

    //std::cout << "Ammo : " << equipedWeapon->getAmmo() << '\n';

    //equipedWeapon->setAmmo(250);

    //std::cout << "Ammo : " << equipedWeapon->getAmmo() << '\n';

    return 0;
}
