cmake_minimum_required(VERSION 3.10)

project("Stirling Engine"
VERSION 0.1.0
DESCRIPTION "The USCC's 3D game engine"
LANGUAGES CXX)

add_executable(stirling-engine main.cpp)
install(TARGETS stirling-engine)