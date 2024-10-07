// include/config_manager.hpp

#ifndef CONFIG_MANAGER_HPP
#define CONFIG_MANAGER_HPP

#include <string>
#include "json.hpp"

class ConfigManager {
public:
    ConfigManager();
    bool loadConfig();
    bool saveConfig();
    bool initialSetup();
    void editConfig();

    // Getters
    std::string getInstallDirectory() const;
    bool isAutoUpdateEnabled() const;
    nlohmann::json getConfig() const;

private:
    nlohmann::json config;
    std::string configPath;

    void createDefaultConfig();
};

#endif // CONFIG_MANAGER_HPP