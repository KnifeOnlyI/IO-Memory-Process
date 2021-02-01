#ifndef IOMEMORYPROCESS_PROCESS_HPP
#define IOMEMORYPROCESS_PROCESS_HPP

#include <Windows.h>
#include <vector>

/**
 * Represent a process
 *
 * \author Dany Pignoux (dany.pignoux@outlook.fr)
 */
class Process
{
public:

    /**
     * Create new process representation
     *
     * \param handle The handle
     * \param address The module base address
     */
    Process(HANDLE handle, uintptr_t address);

    /**
     * Get physical address from specified virtual address and offsets
     *
     * \param virtualAddress The virtual address
     * \param offsets The offsets
     *
     * \return The phsysical address from the specified virtual address and offsets
     */
    [[nodiscard]] uintptr_t
    getAddressFromOffsets(uintptr_t virtualAddress, const std::vector<unsigned int> &offsets) const;

    /**
     * Read specified bytes size from the specified address and put in the specified buffer
     *
     * \param address The address
     * \param buffer The buffer
     * \param size The size to read
     */
    void read(uintptr_t address, void *buffer, size_t size) const;

    /**
     * Write specified bytes size buffer into the specified address
     *
     * \param address The address
     * \param buffer The buffer
     * \param size The size to read
     */
    void write(uintptr_t address, void *buffer, size_t size) const;

private:

    HANDLE _handle;         /** \var The handle */
    uintptr_t _address;     /** \var The module base address */
};

#endif //IOMEMORYPROCESS_PROCESS_HPP
