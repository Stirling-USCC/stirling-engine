#include "engine.hpp"

#include <format>
#include <stdexcept>

// This needs to come before the SDL includes
#include <glad/gl.h>

#include "SDL3/SDL_log.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>

Engine::Engine(int argc, char *argv[]) : world_(argc, argv) {
  // Initialize SDL. We specifically need the video subsystem, which facilitates
  // creating windows.
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    throw std::runtime_error(
        std::format("Could not initialize SDL: {}", SDL_GetError()));
  }

  // Create the main window
  window_ = SDL_CreateWindow("Stirling Engine", DEFAULT_WIDTH, DEFAULT_HEIGHT,
                             SDL_WINDOW_OPENGL);
  if (window_ == nullptr) {
    throw std::runtime_error(
        std::format("Could not create main window: {}", SDL_GetError()));
  }

  // Set OpenGL 3.3 as the desired context version
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // Create the OpenGL context
  gl_context_ = SDL_GL_CreateContext(window_);
  if (gl_context_ == nullptr) {
    throw std::runtime_error(
        std::format("Could not create OpenGL context: {}", SDL_GetError()));
  }

  // Load the OpenGL functions
  int gl_version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
  if (gl_version == 0) {
    throw std::runtime_error("Could not load OpenGL functions");
  }
  SDL_Log("Loaded OpenGL version %d.%d", GLAD_VERSION_MAJOR(gl_version),
          GLAD_VERSION_MINOR(gl_version));
}

Engine::~Engine() {
  if (gl_context_) {
    SDL_GL_DestroyContext(gl_context_);
  }

  if (window_) {
    SDL_DestroyWindow(window_);
  }

  SDL_Quit();
}

void Engine::run() {
  if (!SDL_GL_MakeCurrent(window_, gl_context_)) {
    throw std::runtime_error(std::format(
        "Could not make OpenGL context current: {}", SDL_GetError()));
  }

  while (true) {
    // Process all pending events
    // See the documentation of SDL_PollEvent() for more information
    for (SDL_Event e; SDL_PollEvent(&e);) {
      // Handle event
      if (!onEvent(e)) {
        return; // onEvent() returned false, we should terminate
      }
    }
  }
}

bool Engine::onEvent(SDL_Event &e) {
  switch (e.type) {
  case SDL_EVENT_QUIT:
    // User closed the window
    return false; // Stop running
  }
  return true; // Continue running
}