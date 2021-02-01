#include "game/EquipedWeapon.hpp"

EquipedWeapon::EquipedWeapon(std::shared_ptr<Process> &process)
    : _process {process}
{
    //_ammoAddress = process->getAddressFromOffsets(_virtualAddress, _offsets);
    _ammoAddress = process->getAddressFromOffsets(0x1100F8, {0x0, 0x438, 0x1F0, 0x18, 0x1DC, 0x8, 0x150});
    //_ammoAddress = process->getAddressFromOffsets(0x0C1B6E20, {0x150, 0x8, 0x1DC, 0x18, 0x1F0, 0x438, 0x0});
    //_ammoAddress = 0x1C757CF5070;
}

unsigned int EquipedWeapon::getAmmo() const
{
    unsigned int ammo {0};

    //_process->read(_ammoAddress, &ammo, sizeof(ammo));
    _process->read(0x026FA880, &ammo, sizeof(ammo));

    return ammo;
}

void EquipedWeapon::setAmmo(unsigned int value)
{
    _process->write(_ammoAddress, &value, sizeof(value));
}
