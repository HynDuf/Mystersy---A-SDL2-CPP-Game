#include <texture_manager.h>

SDL_Texture *TextureManager::LoadTexture(const char *filename)
{
    SDL_Surface *tmpSurface = IMG_Load(filename);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    return tex;
}