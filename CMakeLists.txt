# Define the minimum supported version of CMake
cmake_minimum_required(VERSION 3.10)

project("Stirling Engine"
VERSION 0.1.0
DESCRIPTION "The USCC's 3D game engine"
LANGUAGES CXX)

# Set the C++ standard (we use C++20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add a .gitignore to the build directory, we *never* want any files in there to be committed!
if(NOT PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  file(GENERATE OUTPUT .gitignore CONTENT "*")
endif()

# Compile the executable program from the listed source files
add_executable(stirling-engine main.cpp)
# Install the engine (only performed if you explicitly tell CMake to install)
install(TARGETS stirling-engine)