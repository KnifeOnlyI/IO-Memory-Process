#ifndef IOMEMORYPROCESS_EQUIPEDWEAPON_HPP
#define IOMEMORYPROCESS_EQUIPEDWEAPON_HPP

#include <memory>

#include "proc/Process.hpp"

/**
 * Represent the equiped weapon
 *
 * \author Dany Pignoux (dany.pignoux@outlook.fr)
 */
class EquipedWeapon
{
public:

    /**
     * Create new equiped weapon representation
     *
     * \param process The process
     */
    explicit EquipedWeapon(std::shared_ptr<Process> &process);

    /**
     * Get the ammo
     *
     * \return The ammot
     */
    [[nodiscard]] unsigned int getAmmo() const;

    /**
     * Set the ammo
     *
     * \param value The new value
     */
    void setAmmo(unsigned int value);

private:

    /**
     * \var The process
     */
    std::shared_ptr<Process> _process;

    /**
     * \var The ammo address
     */
    uintptr_t _ammoAddress;

    /**
     * \var The virtual address
     */
    uintptr_t _virtualAddress {0x070A17E0};

    /**
     * The offsets
     */
    const std::vector<unsigned int> _offsets {0xC8, 0x6B8, 0x3E8, 0x100, 0x5C0, 0x800};
};

#endif //IOMEMORYPROCESS_EQUIPEDWEAPON_HPP
