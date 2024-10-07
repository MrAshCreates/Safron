// include/admin_access.hpp

#ifndef ADMIN_ACCESS_HPP
#define ADMIN_ACCESS_HPP

#include <string>
#include <vector>

class AdminAccess {
public:
    static bool executeCommand(const std::vector<std::string>& command, const std::string& workingDirectory = "");
};

#endif // ADMIN_ACCESS_HPP