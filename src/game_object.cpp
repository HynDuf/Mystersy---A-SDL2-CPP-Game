#include <game_object.h>
#include <texture_manager.h>
GameObject::GameObject(const char *texture_file, SDL_Renderer *ren, int orig_xpos, int orig_ypos)
{
    renderer = ren;
    obj_texture = TextureManager::LoadTexture(texture_file, ren);
    xpos = orig_xpos;
    ypos = orig_ypos;
    dest_rec.x = xpos;
    dest_rec.y = ypos;
}

void GameObject::Update()
{
    dest_rec.h = 60;
    dest_rec.w = 60;
    dest_rec.x++;
    dest_rec.y++;
}

void GameObject::Render()
{
    SDL_RenderCopy(renderer, obj_texture, NULL, &dest_rec);
}