cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(SafronCLI VERSION 0.1)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the directories
include_directories(include)

# Add the executable
add_executable(safron src/main.cpp)

# Set the output directory
set_target_properties(safron PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# The end of CMakeLists.txt

# Installation paths
install(TARGETS safron DESTINATION /usr/local/bin)