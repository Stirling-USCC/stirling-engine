/**
 * @file main.cpp
 * @brief Contains the main() function, where execution begins.
 */

#include <SDL3/SDL_main.h>

#include "engine.hpp"

int main(int argc, char *argv[]) {
  // Create and run an Engine
  Engine engine(argc, argv);
  engine.run();
  return 0; // Success
}