#include <iostream>
#include "CLI11.hpp"
#include "config_manager.hpp"
#include "package_manager.hpp"

int main(int argc, char* argv[]) {
    CLI::App app{"Safron CLI Tool"};

    // Load configuration
    ConfigManager configManager;
    if (!configManager.loadConfig()) {
        std::cerr << "Failed to load configuration. Run 'safron --setup' to initialize." << std::endl;
        return 1;
    }

    // Define command-line options and flags
    app.set_help_all_flag("--help-all", "Expand all help messages");

    // Flag: Setup
    bool setup_flag = false;
    app.add_flag("--setup", setup_flag, "Setup Safron for first-time use");

    // Flag: Edit Config
    bool edit_config_flag = false;
    app.add_flag("--config", edit_config_flag, "Edit the Safron configuration");

    // Subcommand: Install
    auto install_cmd = app.add_subcommand("install", "Install packages");
    std::vector<std::string> packages_to_install;
    install_cmd->add_option("packages", packages_to_install, "Package names or GitHub URLs")->required()->take_all();

    // Subcommand: Update
    auto update_cmd = app.add_subcommand("update", "Update packages");
    std::vector<std::string> packages_to_update;
    update_cmd->add_option("packages", packages_to_update, "Package names or GitHub URLs")->take_all();

    // Subcommand: Remove
    auto remove_cmd = app.add_subcommand("remove", "Remove packages");
    std::vector<std::string> packages_to_remove;
    remove_cmd->add_option("packages", packages_to_remove, "Package names or GitHub URLs")->required()->take_all();

    // Subcommand: Search
    auto search_cmd = app.add_subcommand("search", "Search for packages");
    std::string search_query;
    search_cmd->add_option("query", search_query, "Search query")->required();

    // Subcommand: List Installed Packages
    auto list_cmd = app.add_subcommand("list", "List installed packages");

    CLI11_PARSE(app, argc, argv);

    // Handle --setup flag
    if (setup_flag) {
        if (configManager.initialSetup()) {
            std::cout << "Safron setup completed successfully." << std::endl;
        } else {
            std::cerr << "Safron setup failed." << std::endl;
        }
        return 0;
    }

    // Handle --config flag
    if (edit_config_flag) {
        configManager.editConfig();
        return 0;
    }

    // Create PackageManager instance
    PackageManager packageManager(configManager);

    // Handle subcommands
    if (install_cmd->parsed()) {
        packageManager.installPackages(packages_to_install);
    } else if (update_cmd->parsed()) {
        packageManager.updatePackages(packages_to_update);
    } else if (remove_cmd->parsed()) {
        packageManager.removePackages(packages_to_remove);
    } else if (search_cmd->parsed()) {
        packageManager.searchPackages(search_query);
    } else if (list_cmd->parsed()) {
        packageManager.listInstalledPackages();
    } else {
        std::cout << app.help() << std::endl;
    }

    return 0;
}