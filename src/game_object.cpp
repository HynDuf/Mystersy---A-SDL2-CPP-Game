#include <game_object.h>
#include <texture_manager.h>
GameObject::GameObject(const char *texture_file, int orig_xpos, int orig_ypos)
{
    obj_texture = TextureManager::LoadTexture(texture_file);
    xpos = orig_xpos;
    ypos = orig_ypos;
    dest_rec.x = xpos;
    dest_rec.y = ypos;
    dest_rec.h = 60;
    dest_rec.w = 60;
}

void GameObject::Update()
{
    dest_rec.x++;
    dest_rec.y++;
}

void GameObject::Render()
{
    TextureManager::Draw(obj_texture, dest_rec);
}