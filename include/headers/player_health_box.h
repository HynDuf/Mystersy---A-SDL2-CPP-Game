#pragma once

#include <SDL_ttf.h>
#include <sprite_component.h>
#include <transform_component.h>
#include <string>
#include <algorithm>
class PlayerHealthBox
{
public:
    PlayerHealthBox(int _full_health);
    ~PlayerHealthBox();

    void Update(int health);
    void Render();
    std::string IntToString(int x);
    TTF_Font* font;
    TransformComponent *transform;
    SpriteComponent *sprite;

    SDL_Rect box_rect;
    SDL_Color Black = {255, 255, 255};
    SDL_Surface* surface;
    SDL_Texture* Message;

    int full_health;
};