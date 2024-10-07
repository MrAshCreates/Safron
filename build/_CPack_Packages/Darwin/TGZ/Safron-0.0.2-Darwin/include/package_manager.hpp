// include/package_manager.hpp

#ifndef PACKAGE_MANAGER_HPP
#define PACKAGE_MANAGER_HPP

#include <string>
#include <vector>
#include "config_manager.hpp"

class PackageManager {
public:
    PackageManager(ConfigManager& configManager);

    void installPackages(const std::vector<std::string>& packages);
    void updatePackages(const std::vector<std::string>& packages);
    void removePackages(const std::vector<std::string>& packages);
    void searchPackages(const std::string& query);
    void listInstalledPackages();

private:
    ConfigManager& configManager;

    void installPackage(const std::string& package);
    void updatePackage(const std::string& package);
    void removePackage(const std::string& package);

    bool isGitUrl(const std::string& url);
    bool downloadAndInstallRelease(const std::string& repoUrl);
    bool cloneAndBuildRepo(const std::string& repoUrl);

    void addPackageToConfig(const std::string& packageName);
    void removePackageFromConfig(const std::string& packageName);

    // Helper functions
    std::string sanitizeInput(const std::string& input);
};

#endif // PACKAGE_MANAGER_HPP