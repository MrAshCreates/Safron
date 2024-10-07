cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(SafronCLI VERSION 0.1)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the directories
include_directories(include)

# FetchContent for CLI11
include(FetchContent)

FetchContent_Declare(
    cli11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.3.2  # Use the latest stable version
)

FetchContent_MakeAvailable(cli11)

FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.2  # Use the latest stable version
)

FetchContent_MakeAvailable(json)

# Add the executable
add_executable(safron src/main.cpp)

# Link CLI11 library
target_link_libraries(safron PRIVATE CLI11::CLI11 nlohmann_json::nlohmann_json)

# Set the output directory
set_target_properties(safron PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# The end of CMakeLists.txt

# Installation paths
install(TARGETS safron DESTINATION /usr/local/bin)