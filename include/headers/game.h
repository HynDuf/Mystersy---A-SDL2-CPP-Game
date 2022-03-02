#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
class Game
{
public: 
    Game();
    ~Game();

    void Init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    void HandleEvents();
    void Update();
    void Render();
    void Clean();
    bool Running() {return is_running;}
    static SDL_Renderer *renderer;
    static SDL_Event event;
    static const Uint8 *keyboard_state;
    
    
private:
    bool is_running;
    SDL_Window *window;
};