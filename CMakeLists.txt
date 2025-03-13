# File: CMakeLists.txt
# This is a build configuration that tells the CMake build system how to compile our project

# Define the minimum supported version of CMake
cmake_minimum_required(VERSION 3.14)

project("Stirling Engine"
VERSION 0.1.0
DESCRIPTION "The USCC's 3D game engine"
LANGUAGES CXX)

## Global Compiler Options:
# Set the C++ standard (we use C++20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add a .gitignore to the build directory, we *never* want any files in there to be committed!
if(NOT PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  file(GENERATE OUTPUT .gitignore CONTENT "*")
endif()

## Dependencies:
# Include a handy helper script to automatically fetch and build the libraries we use
include(cmake/CPM.cmake)

# Add SDL3, a cross-platform library for windows, graphics and audio
CPMFindPackage(NAME SDL3
VERSION 3.2.8
GIT_REPOSITORY "https://github.com/libsdl-org/sdl"
# SDL's tags are named differently, so we have to specify this manually
GIT_TAG release-3.2.8
# We don't need the shared library, tests, or to install SDL, turn those off
OPTIONS "SDL_STATIC ON" "SDL_SHARED OFF" "SDL_TESTS OFF" "SDL_DISABLE_INSTALL ON")
# Add Flecs, a fantastic Entity Component System library
CPMFindPackage(NAME flecs
VERSION 4.0.4
GIT_REPOSITORY "https://github.com/SanderMertens/flecs"
# We don't need the shared library, don't bother building it
Options "FLECS_SHARED OFF")

## Main Executable:
# Compile the executable program from the listed source files
# WIN32 creates a GUI (not command line) program on Windows, and is ignored on other operating systems
add_executable(stirling-engine WIN32
src/engine.cpp
src/main.cpp)

# Tell the compiler where to find our headers
target_include_directories(stirling-engine PRIVATE ./include)
# Tell the compiler what libraries we use
target_link_libraries(stirling-engine PRIVATE flecs_static SDL3::SDL3-static)

# Install the engine (only performed if you explicitly tell CMake to install)
install(TARGETS stirling-engine)

## Documentation:
# Generate documentation from comments in the code, with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
SET(DOXYGEN_BUILTIN_STL_SUPPORT YES)
set(DOXYGEN_EXTRACT_PRIVATE YES)
set(DOXYGEN_EXTRACT_STATIC YES)
set(DOXYGEN_FORCE_LOCAL_INCLUDES YES)
set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)
# Build the documentation from header and sources files
  doxygen_add_docs(docs
  ./include
  ./src
  README.md)
endif()