/**
 * @file engine.hpp
 * @briefDefines the main Engine class.
 */

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>

/**
 * @brief The main class used to create and run the game engine.
 * An instance of this class should be created in the main() function, and
 * Engine::run() should be called to start the engine's main game loop.
 */
class Engine {
private:
  static const int DEFAULT_WIDTH = 800;  /**< Default window width */
  static const int DEFAULT_HEIGHT = 600; /**< Default window height */

  SDL_Window *window_ = nullptr;       /**< The main window */
  SDL_GLContext gl_context_ = nullptr; /**< The OpenGL context */

public:
  /**
   * @brief Construct a new engine.
   * You should pass the command-line arguments provided to your main() function
   * in argc and argv
   * @param argc The number of command-line arguments
   * @param argv An array of command-line arguments
   */
  Engine(int argc, char *argv[]);
  /** Destroy the engine. */
  ~Engine();

  /**
   * @brief Run the engine's main loop.
   *
   * If this function returns normally, the engine terminated with a success
   * status. An exception is thrown if any error occurs when running the engine.
   */
  void run();

private:
  /**
   * @brief Process an SDL event.
   *
   * @param e The received SDL event
   * @return A boolean, indicating whether the Engine should continue running
   */
  bool onEvent(SDL_Event &e);
};

#endif // ENGINE_HPP_