#include <game_object.h>
#include <texture_manager.h>
GameObject::GameObject(const char *texture_file, int orig_xpos, int orig_ypos)
{
    obj_texture = TextureManager::LoadTexture(texture_file);
    xpos = orig_xpos;
    ypos = orig_ypos;
    dest_rect.x = xpos;
    dest_rect.y = ypos;
    dest_rect.h = 60;
    dest_rect.w = 60;
    src_rect.x = src_rect.y = 0;
    src_rect.h = src_rect.w = 200;
}

void GameObject::Update()
{
    dest_rect.x++;
    dest_rect.y++;
}

void GameObject::Render()
{
    TextureManager::Draw(obj_texture, src_rect, dest_rect);
}