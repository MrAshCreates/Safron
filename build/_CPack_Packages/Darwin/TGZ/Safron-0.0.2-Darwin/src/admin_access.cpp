// src/admin_access.cpp

#include "admin_access.hpp"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>

bool AdminAccess::executeCommand(const std::vector<std::string>& command, const std::string& workingDirectory) {
    if (command.empty()) {
        std::cerr << "Empty command provided." << std::endl;
        return false;
    }

    pid_t pid = fork();
    if (pid == 0) {
        // Child process

        // Change working directory if specified
        if (!workingDirectory.empty()) {
            if (chdir(workingDirectory.c_str()) != 0) {
                std::cerr << "Failed to change directory to " << workingDirectory << std::endl;
                exit(EXIT_FAILURE);
            }
        }

        // Convert command vector to char* array
        std::vector<char*> args;
        for (const auto& arg : command) {
            args.push_back(const_cast<char*>(arg.c_str()));
        }
        args.push_back(nullptr);

        // Execute command
        if (execvp(args[0], args.data()) == -1) {
            std::cerr << "Failed to execute command: " << args[0] << std::endl;
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        // Fork failed
        std::cerr << "Failed to fork process." << std::endl;
        return false;
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        return (status == 0);
    }
    return false;
}