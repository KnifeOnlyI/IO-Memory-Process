#include "game/EquipedWeapon.hpp"

EquipedWeapon::EquipedWeapon(std::shared_ptr<Process> &process)
    : _process {process}
{
    _ammoAddress = process->getAddressFromOffsets(
        0x70A5BF8, {0xE0, 0x120, 0xA8, 0x50, 0x78, 0x10, 0x20}
    );   // Resident evil 2 Remake
    //_ammoAddress = process->getAddressFromOffsets(0x1100F8, {0x0, 0x438, 0x1F0, 0x18, 0x1DC, 0x8, 0x150}); // Assault cube
}

unsigned int EquipedWeapon::getAmmo() const
{
    unsigned int ammo {0};

    _process->read(_ammoAddress, &ammo, sizeof(ammo));

    return ammo;
}

void EquipedWeapon::setAmmo(unsigned int value)
{
    _process->write(_ammoAddress, &value, sizeof(value));
}
