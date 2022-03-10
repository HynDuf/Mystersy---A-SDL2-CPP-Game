#include <sprite_component.h>
SpriteComponent::SpriteComponent() {}
SpriteComponent::SpriteComponent(const char *texture_file, TransformComponent *_transform)
{
    SetTexture(texture_file);
    transform = _transform;
    animated = true;
    Init();
}
SpriteComponent::SpriteComponent(const char *texture_file, TransformComponent *_transform, int _w, int _h)
{
    SetTexture(texture_file);
    transform = _transform;
    animated = false;
    anim_width = _w;
    anim_height = _h;
    Init();
}
SpriteComponent::~SpriteComponent() 
{
    SDL_DestroyTexture(texture);
}
void SpriteComponent::SetTexture(const char *texture_file)
{
    texture = TextureManager::LoadTexture(texture_file);
}
void SpriteComponent::Init()
{
    src_rect.x = src_rect.y = 0;
    
    dest_rect.h = transform->h;
    dest_rect.w = transform->w;

}

void SpriteComponent::Update()
{
    if (animated)
    {
        src_rect.x = anim_width * static_cast<int> ((SDL_GetTicks() / speed) % frames);
    }
    src_rect.y = anim_index;
    src_rect.w = anim_width;
    src_rect.h = anim_height;
    // NOTE: Update position of transform first
    dest_rect.x = transform->x;
    dest_rect.y = transform->y;
}
void SpriteComponent::Draw()
{
    TextureManager::Draw(texture, src_rect, dest_rect);
}
void SpriteComponent::Draw(int deltax, int deltay)
{
    dest_rect.x += deltax;
    dest_rect.y += deltay;
    TextureManager::Draw(texture, src_rect, dest_rect);
}

void SpriteComponent::ApplyAnimation(const std::string &animation_name)
{
    // 'animation_name' must be already in 'animations_map'
    anim_index = animations_map[animation_name].index_row;
    anim_width = animations_map[animation_name].width;
    anim_height = animations_map[animation_name].height;
    frames = animations_map[animation_name].frames;
    speed = animations_map[animation_name].speed;
}