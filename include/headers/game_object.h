#pragma once
#include <game.h>

class GameObject 
{
public:
    GameObject(const char *texture_file, SDL_Renderer *ren, int orig_xpos, int orig_ypos);
    ~GameObject();

    void Update();
    void Render();
private:
    int xpos;
    int ypos;

    SDL_Texture *obj_texture;
    SDL_Rect src_rect, dest_rec;
    SDL_Renderer *renderer;
};