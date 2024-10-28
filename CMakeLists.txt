# File: CMakeLists.txt
# This is a build configuration that tells the CMake build system how to compile our project

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

## Dependencies:
include(FetchContent)

# SDL3, cross-platform library for creating windows, getting kb/mouse input, etc
# We want to build a static librrary, so that SDL3 is included directly in our executable
set(SDL_SHARED OFF)
set(SDL_STATIC ON)
FetchContent_Declare(SDL3
# TODO: Pin this to a specific git tag when SDL 3.2 is officially released
GIT_REPOSITORY https://github.com/libsdl-org/sdl
GIT_TAG main
# Tells CMake to look for an existing installation of SDL3 on your system, and only download it if you don't have one
FIND_PACKAGE_ARGS NAMES SDL3 COMPONENTS SDL3-static)

FetchContent_MakeAvailable(SDL3)

# Compile the executable program from the listed source files
# WIN32 creates a GUI (not command line) program on Windows, and is ignored on other operating systems
add_executable(stirling-engine WIN32
src/main.cpp)

# Tell the compiler where to find our headers
target_include_directories(stirling-engine PRIVATE ./include)
# Tell the compiler what libraries we use
target_link_libraries(stirling-engine PRIVATE SDL3::SDL3-static)

# Install the engine (only performed if you explicitly tell CMake to install)
install(TARGETS stirling-engine)