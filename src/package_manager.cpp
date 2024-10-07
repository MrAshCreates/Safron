// src/package_manager.cpp

#include "package_manager.hpp"
#include "admin_access.hpp"
#include "build_manager.hpp"
#include "json.hpp"
#include <iostream>
#include <regex>
#include <filesystem>
#include <algorithm>
#include <curl/curl.h>  // For downloading releases

namespace fs = std::filesystem;
using json = nlohmann::json;

// Helper function for CURL write callback
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

PackageManager::PackageManager(ConfigManager& configManager) : configManager(configManager) {}

void PackageManager::installPackage(const std::string& package) {
    std::string sanitizedPackage = sanitizeInput(package);
    std::cout << "Installing package: " << sanitizedPackage << std::endl;

    if (isGitUrl(sanitizedPackage)) {
        // Handle Git repository
        if (!downloadAndInstallRelease(sanitizedPackage)) {
            if (!cloneAndBuildRepo(sanitizedPackage)) {
                std::cerr << "Failed to install package from Git repository: " << sanitizedPackage << std::endl;
                return;
            }
        }
        addPackageToConfig(sanitizedPackage);
    } else {
        // Install via system package manager
        bool success = false;
#ifdef __APPLE__
        std::vector<std::string> command = {"brew", "install", sanitizedPackage};
        success = AdminAccess::executeCommand(command);
#elif __linux__
        std::vector<std::string> command = {"sudo", "apt-get", "install", "-y", sanitizedPackage};
        success = AdminAccess::executeCommand(command);
#elif _WIN32
        std::vector<std::string> command = {"choco", "install", sanitizedPackage, "-y"};
        success = AdminAccess::executeCommand(command);
#else
        std::cerr << "Unsupported OS for package installation." << std::endl;
        return;
#endif
        if (success) {
            std::cout << "Package installed successfully." << std::endl;
            addPackageToConfig(sanitizedPackage);
        } else {
            std::cerr << "Package installation failed." << std::endl;
        }
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
    // Implement actual search logic, possibly querying a package database or API
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
    std::string sanitizedPackage = sanitizeInput(package);
    std::cout << "Installing package: " << sanitizedPackage << std::endl;

    if (isGitUrl(sanitizedPackage)) {
        // Handle Git repository
        if (!downloadAndInstallRelease(sanitizedPackage)) {
            if (!cloneAndBuildRepo(sanitizedPackage)) {
                std::cerr << "Failed to install package from Git repository: " << sanitizedPackage << std::endl;
                return;
            }
        }
        addPackageToConfig(sanitizedPackage);
    } else {
        // Install via system package manager
#ifdef __APPLE__
        std::vector<std::string> command = {"brew", "install", sanitizedPackage};
#elif __linux__
        std::vector<std::string> command = {"sudo", "apt-get", "install", "-y", sanitizedPackage};
#else
        std::cerr << "Unsupported OS for package installation." << std::endl;
        return;
#endif
        if (AdminAccess::executeCommand(command)) {
            std::cout << "Package installed successfully." << std::endl;
            addPackageToConfig(sanitizedPackage);
        } else {
            std::cerr << "Package installation failed." << std::endl;
        }
    }
}

void PackageManager::updatePackage(const std::string& package) {
    std::string sanitizedPackage = sanitizeInput(package);
    std::cout << "Updating package: " << sanitizedPackage << std::endl;

    if (isGitUrl(sanitizedPackage)) {
        // Handle Git repository
        // Assuming the repository was cloned into a directory named after the repo
        std::string repo_name = sanitizedPackage.substr(sanitizedPackage.find_last_of('/') + 1);
        if (repo_name.ends_with(".git")) {
            repo_name = repo_name.substr(0, repo_name.size() - 4);
        }
        std::string install_dir = configManager.getInstallDirectory() + "/" + repo_name;

        if (fs::exists(install_dir)) {
            std::vector<std::string> command = {"git", "-C", install_dir, "pull"};
            if (AdminAccess::executeCommand(command)) {
                // Rebuild the project
                BuildManager buildManager;
                if (buildManager.buildProject(install_dir)) {
                    std::cout << "Package updated successfully." << std::endl;
                } else {
                    std::cerr << "Failed to build the updated project." << std::endl;
                }
            } else {
                std::cerr << "Failed to update the repository." << std::endl;
            }
        } else {
            std::cerr << "Package not found locally. Consider installing it first." << std::endl;
        }
    } else {
        // Update via system package manager
#ifdef __APPLE__
        std::vector<std::string> command = {"brew", "upgrade", sanitizedPackage};
#elif __linux__
        std::vector<std::string> command = {"sudo", "apt-get", "update", "&&", "sudo", "apt-get", "upgrade", "-y", sanitizedPackage};
#else
        std::cerr << "Unsupported OS for package update." << std::endl;
        return;
#endif
        if (AdminAccess::executeCommand(command)) {
            std::cout << "Package updated successfully." << std::endl;
        } else {
            std::cerr << "Package update failed." << std::endl;
        }
    }
}

void PackageManager::removePackage(const std::string& package) {
    std::string sanitizedPackage = sanitizeInput(package);
    std::cout << "Removing package: " << sanitizedPackage << std::endl;

    if (isGitUrl(sanitizedPackage)) {
        // Handle Git repository
        std::string repo_name = sanitizedPackage.substr(sanitizedPackage.find_last_of('/') + 1);
        if (repo_name.ends_with(".git")) {
            repo_name = repo_name.substr(0, repo_name.size() - 4);
        }
        std::string install_dir = configManager.getInstallDirectory() + "/" + repo_name;
        if (fs::remove_all(install_dir)) {
            std::cout << "Package removed successfully." << std::endl;
            removePackageFromConfig(sanitizedPackage);
        } else {
            std::cerr << "Failed to remove package directory." << std::endl;
        }
    } else {
        // Remove via system package manager
#ifdef __APPLE__
        std::vector<std::string> command = {"brew", "uninstall", sanitizedPackage};
#elif __linux__
        std::vector<std::string> command = {"sudo", "apt-get", "remove", "-y", sanitizedPackage};
#else
        std::cerr << "Unsupported OS for package removal." << std::endl;
        return;
#endif
        if (AdminAccess::executeCommand(command)) {
            std::cout << "Package removed successfully." << std::endl;
            removePackageFromConfig(sanitizedPackage);
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
    // Extract owner and repo name
    std::smatch match;
    std::regex regex(R"(github\.com/([\w\-]+)/([\w\-]+))");
    if (std::regex_search(repoUrl, match, regex) && match.size() >= 3) {
        std::string owner = match[1];
        std::string repo = match[2];

        // Build API URL
        std::string api_url = "https://api.github.com/repos/" + owner + "/" + repo + "/releases/latest";

        // Initialize CURL
        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, api_url.c_str());
            curl_easy_setopt(curl, CURLOPT_USERAGENT, "SafronCLI");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) {
                std::cerr << "Failed to fetch release information." << std::endl;
                return false;
            }
        } else {
            std::cerr << "Failed to initialize CURL." << std::endl;
            return false;
        }

        // Parse JSON response
        auto release_info = json::parse(readBuffer);
        if (release_info.contains("assets") && !release_info["assets"].empty()) {
            std::string download_url = release_info["assets"][0]["browser_download_url"];

            // Download the asset
            std::string filename = configManager.getInstallDirectory() + "/" + release_info["assets"][0]["name"].get<std::string>();
            std::vector<std::string> command = {"curl", "-L", "-o", filename, download_url};

            if (AdminAccess::executeCommand(command)) {
                std::cout << "Downloaded release asset: " << filename << std::endl;
                // Additional steps might be required to install the asset
                return true;
            } else {
                std::cerr << "Failed to download release asset." << std::endl;
                return false;
            }
        } else {
            std::cerr << "No assets found in the latest release." << std::endl;
            return false;
        }
    } else {
        std::cerr << "Invalid GitHub repository URL." << std::endl;
        return false;
    }
}

bool PackageManager::cloneAndBuildRepo(const std::string& repoUrl) {
    std::string repo_name = repoUrl.substr(repoUrl.find_last_of('/') + 1);
    if (repo_name.ends_with(".git")) {
        repo_name = repo_name.substr(0, repo_name.size() - 4);
    }

    std::string install_dir = configManager.getInstallDirectory() + "/" + repo_name;
    if (fs::exists(install_dir)) {
        std::cout << "Repository already cloned. Updating..." << std::endl;
        std::vector<std::string> command = {"git", "-C", install_dir, "pull"};
        if (!AdminAccess::executeCommand(command)) {
            std::cerr << "Failed to update repository." << std::endl;
            return false;
        }
    } else {
        std::vector<std::string> command = {"git", "clone", repoUrl, install_dir};
        if (!AdminAccess::executeCommand(command)) {
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

std::string PackageManager::sanitizeInput(const std::string& input) {
    // Remove potentially dangerous characters
    std::string sanitized = input;
    sanitized.erase(std::remove_if(sanitized.begin(), sanitized.end(), [](char c) {
        return !(std::isalnum(c) || c == '.' || c == '/' || c == ':' || c == '-');
    }), sanitized.end());
    return sanitized;
}