#pragma once
#include <game.h>

class GameObject 
{
public:
    GameObject(const char *texture_file, int orig_xpos, int orig_ypos);
    ~GameObject();

    void Update();
    void Render();
private:
    int xpos;
    int ypos;

    SDL_Texture *obj_texture;
    SDL_Rect src_rect, dest_rect;
    SDL_Renderer *renderer;
};