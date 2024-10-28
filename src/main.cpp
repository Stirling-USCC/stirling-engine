#include <SDL3/SDL_main.h>
#include <SDL3/SDL_messagebox.h>
#include <SDL3/SDL_log.h>

int main(int argc, char *argv[])
{
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Hello, world!");
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Stirling Engine", "Hello, world!", nullptr);
    return 0;
}