// src/admin_access.cpp

#include "admin_access.hpp"
#include <iostream>
#include <cstdlib>

bool AdminAccess::requestAdminAccess(const std::string& command) {
#ifdef _WIN32
    // Windows-specific code (not implemented)
    std::cerr << "Admin access not implemented for Windows." << std::endl;
    return false;
#else
    // Unix-based systems
    std::string full_command = "sudo -S " + command;
    int result = std::system(full_command.c_str());
    return (result == 0);
#endif
}