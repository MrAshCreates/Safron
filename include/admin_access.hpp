// include/admin_access.hpp

#ifndef ADMIN_ACCESS_HPP
#define ADMIN_ACCESS_HPP

#include <string>

class AdminAccess {
public:
    static bool requestAdminAccess(const std::string& command);
};

#endif // ADMIN_ACCESS_HPP