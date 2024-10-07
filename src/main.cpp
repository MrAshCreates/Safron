// main.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <vector>
#include "json.hpp"
#include "CLI11.hpp"

using json = nlohmann::json;

// Function declarations
bool initialSetup();
void editConfig();
json readConfig();
void writeConfig(const json& config);
void installPackage(const std::string& package_name);
void updatePackage(const std::string& package_name);
void removePackage(const std::string& package_name);
bool requestAdminAccess(const std::string& command);
bool confirmAction(const std::string& message);
void logError(const std::string& message, int error_code = 0);

int main(int argc, char* argv[]) {
    CLI::App app{"Safron CLI Tool"};

   // Define command-line options and flags
    app.set_help_all_flag("--help-all", "Expand all help messages");

    // Subcommand: Install
    auto install_cmd = app.add_subcommand("install", "Install a package by name or GitHub URL");
    std::string package_name;
    install_cmd->add_option("package", package_name, "Package name or GitHub URL")->required();

    // Subcommand: Update
    auto update_cmd = app.add_subcommand("update", "Update a package");
    std::string update_package_name;
    update_cmd->add_option("package", update_package_name, "Package name")->required();

    // Subcommand: Remove
    auto remove_cmd = app.add_subcommand("remove", "Remove a package");
    std::string remove_package_name;
    remove_cmd->add_option("package", remove_package_name, "Package name")->required();

    // Flag: Setup
    bool setup_flag = false;
    app.add_flag("--setup", setup_flag, "Setup Safron for first-time use");

    // Flag: Edit Config
    bool edit_config_flag = false;
    app.add_flag("--config", edit_config_flag, "Edit the Safron configuration");

    CLI11_PARSE(app, argc, argv);

    // Handle --setup flag
    if (setup_flag) {
        if (initialSetup()) {
            std::cout << "Safron setup completed successfully." << std::endl;
        } else {
            std::cerr << "Safron setup failed." << std::endl;
        }
        return 0;
    }

    // Handle --config flag
    if (edit_config_flag) {
        editConfig();
        return 0;
    }

    // Load configuration
    json config = readConfig();

    // Handle subcommands
    if (install_cmd->parsed()) {
        std::cout << "Installing package: " << package_name << std::endl;
        installPackage(package_name);
    } else if (update_cmd->parsed()) {
        std::cout << "Updating package: " << update_package_name << std::endl;
        updatePackage(update_package_name);
    } else if (remove_cmd->parsed()) {
        std::cout << "Removing package: " << remove_package_name << std::endl;
        removePackage(remove_package_name);
    } else {
        std::cout << app.help() << std::endl;
    }

    return 0;
}

// Function definitions

bool initialSetup() {
    std::cout << "Performing initial setup..." << std::endl;
    // Create default configuration file
    json default_config = {
        {"auto_update", true},
        {"install_directory", "/usr/local/bin"},
        {"repositories", json::array()}
    };

    writeConfig(default_config);
    return true;
}

void editConfig() {
    json config = readConfig();

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

    writeConfig(config);
    std::cout << "Configuration updated successfully." << std::endl;
}

json readConfig() {
    const std::string config_path = std::string(getenv("HOME")) + "/.safron/config.json";
    std::ifstream config_file(config_path);
    json config;
    if (config_file.is_open()) {
        config_file >> config;
        config_file.close();
    } else {
        std::cerr << "Config file not found. Please run 'safron --setup' to initialize." << std::endl;
        exit(1);
    }
    return config;
}

void writeConfig(const json& config) {
    const std::string config_path = std::string(getenv("HOME")) + "/.safron/config.json";
    std::ofstream config_file(config_path);
    if (config_file.is_open()) {
        config_file << config.dump(4);
        config_file.close();
    } else {
        std::cerr << "ERROR - Failed to write config file!" << std::endl;
    }
}

void installPackage(const std::string& package_name) {
    std::string command;
    if (package_name.find("github.com") != std::string::npos) {
        // Clone repository
        command = "git clone " + package_name;
    } else {
        // Install via package manager
#ifdef __APPLE__
        command = "brew install " + package_name;
#elif __linux__
        command = "sudo apt-get install -y " + package_name;
#else
        std::cerr << "Unsupported OS for package installation." << std::endl;
        return;
#endif
    }

    if (confirmAction("Proceed with installation?")) {
        if (requestAdminAccess(command)) {
            std::cout << "Package installed successfully." << std::endl;
        } else {
            std::cerr << "Package installation failed." << std::endl;
        }
    } else {
        std::cout << "Installation cancelled." << std::endl;
    }
}

void updatePackage(const std::string& package_name) {
    std::string command;
    if (package_name.find("github.com") != std::string::npos) {
        // Pull latest changes
        std::string repo_name = package_name.substr(package_name.find_last_of('/') + 1);
        command = "cd " + repo_name + " && git pull";
    } else {
        // Update via package manager
#ifdef __APPLE__
        command = "brew upgrade " + package_name;
#elif __linux__
        command = "sudo apt-get update && sudo apt-get upgrade -y " + package_name;
#else
        std::cerr << "Unsupported OS for package update." << std::endl;
        return;
#endif
    }

    if (confirmAction("Proceed with update?")) {
        if (requestAdminAccess(command)) {
            std::cout << "Package updated successfully." << std::endl;
        } else {
            std::cerr << "Package update failed." << std::endl;
        }
    } else {
        std::cout << "Update cancelled." << std::endl;
    }
}

void removePackage(const std::string& package_name) {
    std::string command;
    if (package_name.find("github.com") != std::string::npos) {
        // Remove cloned repository
        std::string repo_name = package_name.substr(package_name.find_last_of('/') + 1);
        command = "rm -rf " + repo_name;
    } else {
        // Remove via package manager
#ifdef __APPLE__
        command = "brew uninstall " + package_name;
#elif __linux__
        command = "sudo apt-get remove -y " + package_name;
#else
        std::cerr << "Unsupported OS for package removal." << std::endl;
        return;
#endif
    }

    if (confirmAction("Proceed with removal?")) {
        if (requestAdminAccess(command)) {
            std::cout << "Package removed successfully." << std::endl;
        } else {
            std::cerr << "Package removal failed." << std::endl;
        }
    } else {
        std::cout << "Removal cancelled." << std::endl;
    }
}

bool requestAdminAccess(const std::string& command) {
#ifdef _WIN32
    // Windows-specific code to request admin access (not implemented here)
    std::cerr << "Admin access request not implemented for Windows." << std::endl;
    return false;
#else
    // Unix-based systems
    int result = std::system(command.c_str());
    return (result == 0);
#endif
}

bool confirmAction(const std::string& message) {
    std::string input;
    std::cout << message << " (y/n): ";
    std::getline(std::cin, input);
    return (input == "y" || input == "Y");
}