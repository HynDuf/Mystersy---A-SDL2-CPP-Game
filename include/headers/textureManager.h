#pragma once
#include<game.h>
class textureManager
{
    public:
        static SDL_Texture *loadTexture(const char *filename, SDL_Renderer *renderer);
};