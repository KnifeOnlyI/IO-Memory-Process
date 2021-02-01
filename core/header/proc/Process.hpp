#ifndef IOMEMORYPROCESS_PROCESS_HPP
#define IOMEMORYPROCESS_PROCESS_HPP

#include <Windows.h>
#include <vector>
#include <string>

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
     * \param name The name
     * \param handle The handle
     * \param address The module base address
     */
    Process(std::string name, HANDLE handle, DWORD_PTR address);

    /**
     * Get physical address from specified virtual address and offsets
     *
     * \param virtualAddress The virtual address
     * \param offsets The offsets
     *
     * \return The phsysical address from the specified virtual address and offsets
     */
    [[nodiscard]] uintptr_t
    getAddressFromOffsets(DWORD_PTR virtualAddress, const std::vector<unsigned int> &offsets) const;

    /**
     * Read specified bytes size from the specified address and put in the specified buffer
     *
     * \param address The address
     * \param buffer The buffer
     * \param size The size to read
     */
    void read(DWORD_PTR address, void *buffer, size_t size) const;

    /**
     * Write specified bytes size buffer into the specified address
     *
     * \param address The address
     * \param buffer The buffer
     * \param size The size to read
     */
    void write(DWORD_PTR address, void *buffer, size_t size) const;

private:

    std::string _name;         /** \var The name */
    HANDLE _handle;            /** \var The handle */
    DWORD_PTR _address;        /** \var The module base address */
};

#endif //IOMEMORYPROCESS_PROCESS_HPP
