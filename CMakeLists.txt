cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(Safron VERSION 0.0.2)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the directories
include_directories(include)

# Add the executable
add_executable(safron
    src/main.cpp
    src/config_manager.cpp
    src/package_manager.cpp
    src/build_manager.cpp
    src/admin_access.cpp
)

# Find and link the CURL library
find_package(CURL REQUIRED)
if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    target_link_libraries(safron PRIVATE ${CURL_LIBRARIES})
else()
    message(FATAL_ERROR "Could not find CURL library")
endif()

# Set the output directory
set_target_properties(safron PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Installation paths
install(TARGETS safron DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY src/ DESTINATION src)
install(DIRECTORY resources/ DESTINATION resources)
install(FILES CMakeLists.txt DESTINATION .)

# Include CPack for packaging
include(CPack)

# Set package properties
set(CPACK_PACKAGE_NAME "SafronCLI")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_CONTACT "MrAshCreates git@asherwinstead.dev")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Safron CLI Tool - A versatile package manager")

# Specify the package generators
set(CPACK_GENERATOR "TGZ;ZIP;NSIS")

# Exclude build and VCS directories from the package
set(CPACK_SOURCE_IGNORE_FILES
    "/build/;/\\.git/;~$;${CPACK_SOURCE_IGNORE_FILES}"
)
