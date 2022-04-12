#include <game.h>

const int FPS = 60;
const int FRAME_MAX_DELAY = 1000 / FPS;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 640;
Game *game = nullptr;
Uint32 frame_start;
int frame_time;
int Menu();
int Help();
int Exit();
int PlayGame();
enum 
{
    MENU, 
    HELP, 
    EXIT,
    PLAYGAME
};
int main(int argc, char *argv[])
{
    /**
     * @brief 
     * 0 - Menu.
     * 1 - Help.
     * 2 - Exit.
     * 3 - Play Game.
     */
    int type = MENU;
    
    while (type != EXIT)
    {
        game = new Game();
        switch (type)
        {
            case MENU:
                type = Menu();
                break;
            case HELP:
                type = Help();
                break;
            case EXIT:
                type = Exit();
                break;
            case PLAYGAME:
                type = PlayGame();
                break;
            default:
                break;
        }
        game->Clean();
    }
    
    return 0;
}

int Menu()
{
    game->Init("Mystersy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);
    game->RenderMenu();
    while (1)
    {
        int state = game->UpdateMouse();
        switch (state)
        {
            case MENU:
                game->RenderMenu();
                break;
            case HELP:
                return HELP;
            case EXIT:
                return EXIT;
            case PLAYGAME:
                return PLAYGAME;
            default:
                break;
        }
    }
    return -1;
}
int Help()
{
    game->Init("Mystersy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);
    game->RenderGuide();

    while (1)
    {
        int mousex, mousey;

        SDL_PumpEvents();

        Uint32 buttons = SDL_GetMouseState(&mousex, &mousey);
        if ((buttons & SDL_BUTTON_LMASK) != 0)
            break;
    }
    
    return MENU;
}
int Exit()
{
    return EXIT;
}
int PlayGame()
{
    game->Init("Mystersy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);
    while (game->Running())
    {
        frame_start = SDL_GetTicks();
        game->HandleEvents();
        game->Update(); 
        game->Render();
        if (game->Lost())
        {
            std::cout << "Game Over!\n";
            break;
        }
        if (game->Won())
        {
            std::cout << "Game Won\n";
            break;
        }
        frame_time = SDL_GetTicks() - frame_start;
        if (frame_time < FRAME_MAX_DELAY)
        {
            SDL_Delay(FRAME_MAX_DELAY - frame_time);
        }
    }
    SDL_Event event;
    bool play_again = false;
    while (1)
    {
        bool done = false;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            play_again = false;
                            done = true;
                            break;
                        case SDLK_SPACE:
                            play_again = true;
                            done = true;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        if (done)
            break;
    }
    if (play_again) 
        return MENU;
    return EXIT;
}