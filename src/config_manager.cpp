// src/config_manager.cpp

#include "config_manager.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

ConfigManager::ConfigManager() {
    std::string homeDir;

#ifdef _WIN32
    char* buf = nullptr;
    size_t sz = 0;
    if (_dupenv_s(&buf, &sz, "USERPROFILE") == 0 && buf != nullptr) {
        homeDir = buf;
        free(buf);
    } else {
        std::cerr << "Failed to get USERPROFILE environment variable." << std::endl;
        // Handle error or set a default path
        homeDir = "C:\\Users\\Default";
    }
#else
    const char* envHome = std::getenv("HOME");
    if (envHome) {
        homeDir = envHome;
    } else {
        std::cerr << "Failed to get HOME environment variable." << std::endl;
        // Handle error or set a default path
        homeDir = "/home";
    }
#endif

    configPath = homeDir + "/.safron/config.json";
}

bool ConfigManager::loadConfig() {
    std::ifstream configFile(configPath);
    if (configFile.is_open()) {
        configFile >> config;
        configFile.close();
        return true;
    } else {
        std::cerr << "Config file not found at " << configPath << std::endl;
        return false;
    }
}

bool ConfigManager::saveConfig() {
    std::ofstream configFile(configPath);
    if (configFile.is_open()) {
        configFile << config.dump(4);
        configFile.close();
        return true;
    } else {
        std::cerr << "Failed to write config file at " << configPath << std::endl;
        return false;
    }
}

bool ConfigManager::initialSetup() {
    std::cout << "Performing initial setup..." << std::endl;
    createDefaultConfig();
    return saveConfig();
}

void ConfigManager::editConfig() {
    // Load current config
    if (!loadConfig()) {
        std::cerr << "Failed to load configuration." << std::endl;
        return;
    }

    std::string input;
    std::cout << "Current install directory: " << config["install_directory"] << std::endl;
    std::cout << "Enter new install directory (leave blank to keep current): ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        config["install_directory"] = input;
    }

    std::cout << "Auto-update is currently " << (config["auto_update"] ? "enabled" : "disabled") << std::endl;
    std::cout << "Enable auto-update? (y/n): ";
    std::getline(std::cin, input);
    if (input == "y" || input == "Y") {
        config["auto_update"] = true;
    } else if (input == "n" || input == "N") {
        config["auto_update"] = false;
    }

    if (saveConfig()) {
        std::cout << "Configuration updated successfully." << std::endl;
    }
}

std::string ConfigManager::getInstallDirectory() const {
    return config["install_directory"];
}

bool ConfigManager::isAutoUpdateEnabled() const {
    return config["auto_update"];
}

nlohmann::json ConfigManager::getConfig() const {
    return config;
}

void ConfigManager::createDefaultConfig() {
    std::string installDir;
#ifdef _WIN32
    installDir = "C:\\Program Files\\Safron";
#else
    installDir = "/usr/local/bin";
#endif

    config = {
        {"auto_update", true},
        {"install_directory", installDir},
        {"installed_packages", nlohmann::json::array()}
    };
    // Ensure the directory exists
    fs::create_directories(config["install_directory"].get<std::string>());
}