#ifndef IOMEMORYPROCESS_PROCESSSERVICE_HPP
#define IOMEMORYPROCESS_PROCESSSERVICE_HPP

#include <Windows.h>
#include <string>
#include <vector>
#include <memory>
#include "Process.hpp"

/**
 * Service to manage processes
 *
 * \author Dany Pignoux (dany.pignoux@outlook.fr)
 */
class ProcessService
{
public:

    /**
     * Open the specified process
     *
     * \param name The process name
     * \param access The desired access
     *
     * \return The process representation
     */
    static std::unique_ptr<Process> open(const std::string &name, DWORD access);

    /**
     * Check if process with the specified name exists
     *
     * \param name The process name
     *
     * \return TRUE if the process exists, FALSE otherwise
     */
    static bool exists(const std::string &name);

private:

    /**
     * Get pid of the specified process
     *
     * \param name The process name
     *
     * \return The pid of the specified process
     */
    static DWORD getProcID(const std::string &name);

    /**
     * Get the base address of the specified module
     *
     * \param pid The module pid
     * \param name The module name
     *
     * \return The base address of the specified module
     */
    static uintptr_t getModuleBaseAddress(DWORD pid, const std::string &name);
};

#endif //IOMEMORYPROCESS_PROCESSSERVICE_HPP
