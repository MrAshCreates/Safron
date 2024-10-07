#include "admin_access.hpp"
#include <iostream>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#endif

bool AdminAccess::executeCommand(const std::vector<std::string>& command, const std::string& workingDirectory) {
    if (command.empty()) {
        std::cerr << "Empty command provided." << std::endl;
        return false;
    }

#ifdef _WIN32
    // Windows implementation
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Concatenate the command into a single string
    std::string cmdLine;
    for (const auto& arg : command) {
        cmdLine += "\"" + arg + "\" ";
    }

    // Set working directory
    LPCSTR lpCurrentDirectory = NULL;
    if (!workingDirectory.empty()) {
        lpCurrentDirectory = workingDirectory.c_str();
    }

    // Create the process
    if (!CreateProcessA(
            NULL,
            const_cast<char*>(cmdLine.c_str()),
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            lpCurrentDirectory,
            &si,
            &pi)) {
        std::cerr << "Failed to execute command: " << cmdLine << std::endl;
        return false;
    }

    // Wait until child process exits
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Get the exit code
    DWORD exitCode;
    if (!GetExitCodeProcess(pi.hProcess, &exitCode)) {
        std::cerr << "Failed to get exit code." << std::endl;
        exitCode = 1; // Assume failure
    }

    // Close process and thread handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return (exitCode == 0);
#else
    // Unix implementation
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
#endif
}