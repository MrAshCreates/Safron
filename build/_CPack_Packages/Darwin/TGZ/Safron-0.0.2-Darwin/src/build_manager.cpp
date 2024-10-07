// src/build_manager.cpp

#include "build_manager.hpp"
#include "admin_access.hpp"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

bool BuildManager::buildProject(const std::string& projectPath) {
    std::cout << "Building project at " << projectPath << std::endl;

    // Check if CMakeLists.txt exists
    if (fs::exists(projectPath + "/CMakeLists.txt")) {
        std::vector<std::string> commands = {
            "mkdir", "-p", "build",
            "&&", "cd", "build",
            "&&", "cmake", "..",
            "&&", "make",
            "&&", "sudo", "make", "install"
        };
    } else if (fs::exists(projectPath + "/configure")) {
        std::vector<std::string> commands = {
            "./configure",
            "&&", "make",
            "&&", "sudo", "make", "install"
        };
    } else if (fs::exists(projectPath + "/Makefile")) {
        std::vector<std::string> commands = {
            "make",
            "&&", "sudo", "make", "install"
        };
    } else {
        std::cerr << "No recognized build files found in " << projectPath << std::endl;
        return false;
    }

    // Note: The above command sequences need to be executed properly.
    // For the purposes of this example, we need to implement command execution that supports multiple commands.

    // Implementing command execution with multiple steps would require additional code.
    // For now, we'll simplify and assume the build commands are encapsulated in a script called 'build.sh'.

    if (fs::exists(projectPath + "/build.sh")) {
        std::vector<std::string> command = {"/bin/bash", "build.sh"};
        if (AdminAccess::executeCommand(command, projectPath)) {
            return true;
        } else {
            std::cerr << "Failed to build the project using build.sh." << std::endl;
            return false;
        }
    } else {
        std::cerr << "No build script found. Cannot build the project." << std::endl;
        return false;
    }
}