#include <player_health_box.h>
#include <game.h>
PlayerHealthBox::PlayerHealthBox(int _full_health)
{
    font = TTF_OpenFont("fonts/number_font.ttf", 15);
    if(font == NULL)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
    }
    transform = new TransformComponent(20, 15, 0, 40, 35);
    sprite = new SpriteComponent("img/player/player_heart.png", transform, false);
    full_health = _full_health;
    box_rect.x = 70;
    box_rect.y = 20;
    box_rect.w = 150;
    box_rect.h = 30;
}

PlayerHealthBox::~PlayerHealthBox() 
{
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(Message);
}
std::string PlayerHealthBox::IntToString(int x)
{
    if (x == 0) 
        return "0";
    std::string res = "";
    while (x)
    {
        res += (x % 10) + '0';
        x /= 10;
    }
    std::reverse(res.begin(), res.end());
    return res;
}
void PlayerHealthBox::Update(int health)
{
    const char *message = (IntToString(health) + "/" + IntToString(full_health)).data();
    surface = TTF_RenderText_Solid(font, message, Black);
    Message = SDL_CreateTextureFromSurface(Game::renderer, surface);
    sprite->Update();
}
void PlayerHealthBox::Render()
{
    SDL_RenderCopy(Game::renderer, Message, NULL, &box_rect);
    sprite->Draw();
}

