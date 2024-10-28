cmake_minimum_required(VERSION 3.10)

project("Stirling Engine"
VERSION 0.1.0
DESCRIPTION "The USCC's 3D game engine"
LANGUAGES CXX)

# Add a .gitignore to the build directory, we *never* want any files in there to be committed!
if(NOT PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  file(GENERATE OUTPUT .gitignore CONTENT "*")
endif()

add_executable(stirling-engine main.cpp)
install(TARGETS stirling-engine)