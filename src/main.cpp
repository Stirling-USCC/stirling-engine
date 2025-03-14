/**
 * @file main.cpp
 * @brief Contains the main() function, where execution begins.
 */

#include <exception>

#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_messagebox.h>

#include "engine.hpp"

int main(int argc, char *argv[]) {
  try {
    // Create and run an Engine
    Engine engine(argc, argv);
    engine.run();
  } catch (const std::exception &e) {
    // Display a message box with the error
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Critical Error", e.what(),
                             nullptr);
    // Log the error using SDL's logging system, in case the message box fails
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", e.what());
    return 1; // Failure
  }
  return 0; // Success
}