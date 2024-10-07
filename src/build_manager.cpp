// src/build_manager.cpp

#include "build_manager.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

bool BuildManager::buildProject(const std::string& projectPath) {
    std::cout << "Building project at " << projectPath << std::endl;

    // Check if CMakeLists.txt exists
    if (fs::exists(projectPath + "/CMakeLists.txt")) {
        std::string command = "cd " + projectPath + " && mkdir -p build && cd build && cmake .. && make && sudo make install";
        if (std::system(command.c_str()) == 0) {
            return true;
        } else {
            std::cerr << "Failed to build the project using CMake." << std::endl;
            return false;
        }
    } else {
        // Try using a generic build command
        std::string command = "cd " + projectPath + " && make && sudo make install";
        if (std::system(command.c_str()) == 0) {
            return true;
        } else {
            std::cerr << "Failed to build the project using Make." << std::endl;
            return false;
        }
    }
}