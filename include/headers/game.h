#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class Game
{
public: 
    Game();
    ~Game();

    void Init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    void HandleEvents();
    void Update();
    void UpdateSound();
    void Render();
    void RenderGameOver();
    void RenderGameWon();
    void Clean();
    bool Running() {return is_running;}
    bool Won();
    bool Lost();

    /**
     * @brief Menu's mouse manager
     */
    int play_button_state = 0;
    int help_button_state = 0;
    int exit_button_state = 0;
    bool InsidePlayButton(int x, int y);
    bool InsideHelpButton(int x, int y);
    bool InsideExitButton(int x, int y);
    int UpdateMouse();
    void RenderMenu();


    void RenderGuide();


    static SDL_Renderer *renderer;
    static const Uint8 *keyboard_state;
    
private:
    bool is_running;
    SDL_Window *window;
};