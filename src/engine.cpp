#include "engine.hpp"

#include <stdexcept>

#include <fmt/core.h>
#include <SDL3/SDL_init.h>

Engine::Engine(int argc, char *argv[])
{
    // Initialize SDL. We specifically need the video subsystem, which facilitates creating windows.
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        throw std::runtime_error(fmt::format("Could not initialize SDL: {}", SDL_GetError()));
    }

    // Create the main window
    window_ = SDL_CreateWindow("Stirling Engine", DEFAULT_WIDTH, DEFAULT_HEIGHT, 0);
    if (window_ == nullptr)
    {
        throw std::runtime_error(fmt::format("Could not create main window: {}", SDL_GetError()));
    }
}

Engine::~Engine()
{
    if (window_)
    {
        SDL_DestroyWindow(window_);
    }

    SDL_Quit();
}

void Engine::run()
{
    while (true)
    {
        // Process all pending events
        // See the documentation of SDL_PollEvent() for more information
        for (SDL_Event e; SDL_PollEvent(&e);)
        {
            // Handle event
            if (!onEvent(e))
            {
                return; // onEvent() returned false, we should terminate
            }
        }
    }
}

bool Engine::onEvent(SDL_Event &e)
{
    switch (e.type)
    {
    case SDL_EVENT_QUIT:
        // User closed the window
        return false; // Stop running
    }
    return true; // Continue running
}