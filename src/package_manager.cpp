// src/package_manager.cpp

#include "package_manager.hpp"
#include "admin_access.hpp"
#include "build_manager.hpp"
#include <iostream>
#include <regex>
#include <filesystem>

namespace fs = std::filesystem;

PackageManager::PackageManager(ConfigManager& configManager) : configManager(configManager) {}

void PackageManager::installPackages(const std::vector<std::string>& packages) {
    for (const auto& package : packages) {
        installPackage(package);
    }
}

void PackageManager::updatePackages(const std::vector<std::string>& packages) {
    for (const auto& package : packages) {
        updatePackage(package);
    }
}

void PackageManager::removePackages(const std::vector<std::string>& packages) {
    for (const auto& package : packages) {
        removePackage(package);
    }
}

void PackageManager::searchPackages(const std::string& query) {
    // Placeholder implementation
    std::cout << "Searching for packages matching: " << query << std::endl;
    // Implement actual search logic
}

void PackageManager::listInstalledPackages() {
    auto config = configManager.getConfig();
    if (config.contains("installed_packages")) {
        std::cout << "Installed Packages:" << std::endl;
        for (const auto& pkg : config["installed_packages"]) {
            std::cout << "- " << pkg.get<std::string>() << std::endl;
        }
    } else {
        std::cout << "No packages installed." << std::endl;
    }
}

void PackageManager::installPackage(const std::string& package) {
    std::cout << "Installing package: " << package << std::endl;

    if (isGitUrl(package)) {
        // Handle Git repository
        if (!downloadAndInstallRelease(package)) {
            if (!cloneAndBuildRepo(package)) {
                std::cerr << "Failed to install package from Git repository: " << package << std::endl;
                return;
            }
        }
        addPackageToConfig(package);
    } else {
        // Install via system package manager
#ifdef __APPLE__
        std::string command = "brew install " + package;
#elif __linux__
        std::string command = "sudo apt-get install -y " + package;
#else
        std::cerr << "Unsupported OS for package installation." << std::endl;
        return;
#endif
        if (AdminAccess::requestAdminAccess(command)) {
            std::cout << "Package installed successfully." << std::endl;
            addPackageToConfig(package);
        } else {
            std::cerr << "Package installation failed." << std::endl;
        }
    }
}

void PackageManager::updatePackage(const std::string& package) {
    std::cout << "Updating package: " << package << std::endl;

    if (isGitUrl(package)) {
        // Handle Git repository
        // Assuming the repository was cloned into a directory named after the repo
        std::string repo_name = package.substr(package.find_last_of('/') + 1);
        if (repo_name.ends_with(".git")) {
            repo_name = repo_name.substr(0, repo_name.size() - 4);
        }
        std::string command = "cd " + repo_name + " && git pull";
        if (std::system(command.c_str()) == 0) {
            std::cout << "Package updated successfully." << std::endl;
        } else {
            std::cerr << "Package update failed." << std::endl;
        }
    } else {
        // Update via system package manager
#ifdef __APPLE__
        std::string command = "brew upgrade " + package;
#elif __linux__
        std::string command = "sudo apt-get update && sudo apt-get upgrade -y " + package;
#else
        std::cerr << "Unsupported OS for package update." << std::endl;
        return;
#endif
        if (AdminAccess::requestAdminAccess(command)) {
            std::cout << "Package updated successfully." << std::endl;
        } else {
            std::cerr << "Package update failed." << std::endl;
        }
    }
}

void PackageManager::removePackage(const std::string& package) {
    std::cout << "Removing package: " << package << std::endl;

    if (isGitUrl(package)) {
        // Handle Git repository
        std::string repo_name = package.substr(package.find_last_of('/') + 1);
        if (repo_name.ends_with(".git")) {
            repo_name = repo_name.substr(0, repo_name.size() - 4);
        }
        std::string install_dir = configManager.getInstallDirectory() + "/" + repo_name;
        if (fs::remove_all(install_dir)) {
            std::cout << "Package removed successfully." << std::endl;
            removePackageFromConfig(package);
        } else {
            std::cerr << "Failed to remove package directory." << std::endl;
        }
    } else {
        // Remove via system package manager
#ifdef __APPLE__
        std::string command = "brew uninstall " + package;
#elif __linux__
        std::string command = "sudo apt-get remove -y " + package;
#else
        std::cerr << "Unsupported OS for package removal." << std::endl;
        return;
#endif
        if (AdminAccess::requestAdminAccess(command)) {
            std::cout << "Package removed successfully." << std::endl;
            removePackageFromConfig(package);
        } else {
            std::cerr << "Package removal failed." << std::endl;
        }
    }
}

bool PackageManager::isGitUrl(const std::string& url) {
    std::regex git_regex(R"(https?://(www\.)?github\.com/[\w\-]+/[\w\-]+(\.git)?/?$)");
    return std::regex_match(url, git_regex);
}

bool PackageManager::downloadAndInstallRelease(const std::string& repoUrl) {
    // Placeholder: Implement logic to download and install the latest release
    // from the GitHub repository's releases page.

    // For now, return false to indicate failure to download release.
    return false;
}

bool PackageManager::cloneAndBuildRepo(const std::string& repoUrl) {
    std::string repo_name = repoUrl.substr(repoUrl.find_last_of('/') + 1);
    if (repo_name.ends_with(".git")) {
        repo_name = repo_name.substr(0, repo_name.size() - 4);
    }

    std::string install_dir = configManager.getInstallDirectory() + "/" + repo_name;
    if (fs::exists(install_dir)) {
        std::cout << "Repository already cloned. Updating..." << std::endl;
        std::string command = "cd " + install_dir + " && git pull";
        if (std::system(command.c_str()) != 0) {
            std::cerr << "Failed to update repository." << std::endl;
            return false;
        }
    } else {
        std::string command = "git clone " + repoUrl + " " + install_dir;
        if (std::system(command.c_str()) != 0) {
            std::cerr << "Failed to clone repository." << std::endl;
            return false;
        }
    }

    // Build the project
    BuildManager buildManager;
    if (buildManager.buildProject(install_dir)) {
        std::cout << "Project built and installed successfully." << std::endl;
        return true;
    } else {
        std::cerr << "Failed to build the project." << std::endl;
        return false;
    }
}

void PackageManager::addPackageToConfig(const std::string& packageName) {
    auto config = configManager.getConfig();
    if (!config.contains("installed_packages")) {
        config["installed_packages"] = nlohmann::json::array();
    }
    config["installed_packages"].push_back(packageName);
    configManager.saveConfig();
}

void PackageManager::removePackageFromConfig(const std::string& packageName) {
    auto config = configManager.getConfig();
    if (config.contains("installed_packages")) {
        auto& packages = config["installed_packages"];
        packages.erase(std::remove(packages.begin(), packages.end(), packageName), packages.end());
        configManager.saveConfig();
    }
}