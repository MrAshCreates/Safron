// include/build_manager.hpp

#ifndef BUILD_MANAGER_HPP
#define BUILD_MANAGER_HPP

#include <string>

class BuildManager {
public:
    bool buildProject(const std::string& projectPath);
};

#endif // BUILD_MANAGER_HPP