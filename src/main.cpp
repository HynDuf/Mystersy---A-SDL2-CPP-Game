#include <SDL.h>
#include <game.h>
#include <SDL.h>

Game *game = nullptr;
const int FPS = 60;
const int frameMaxDelay = 1000 / FPS;

Uint32 frameStart;
int frameTime;
int main(int argc, char *argv[])
{
    game = new Game();
    game->init("Knighty", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
    while (game->running())
    {
        frameStart = SDL_GetTicks();
        game->handleEvents();
        game->update(); 
        game->render();
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameMaxDelay)
        {
            SDL_Delay(frameMaxDelay - frameTime);
        }
    }
    game->clean();
    return 0;
}