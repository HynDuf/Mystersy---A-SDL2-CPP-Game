#include <sprite_component.h>
SpriteComponent::SpriteComponent() {}
SpriteComponent::SpriteComponent(const char *texture_file, TransformComponent *_transform, int _w, int _h, bool _animated)
{
    SetTexture(texture_file);
    animated = _animated;
    transform = _transform;
    src_rect.h = _h;
    src_rect.w = _w;
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
        src_rect.x = src_rect.w * static_cast<int> ((SDL_GetTicks() / speed) % frames);
    }
    src_rect.y = anim_index * transform->h;
    // NOTE: Update position of transform first
    dest_rect.x = transform->x;
    dest_rect.y = transform->y;
}
void SpriteComponent::Draw()
{
    TextureManager::Draw(texture, src_rect, dest_rect);
}

void SpriteComponent::ApplyAnimation(const std::string &animation_name)
{
    // 'animation_name' must be already in 'animations_map'
    frames = animations_map[animation_name].frames;
    speed = animations_map[animation_name].speed;
    anim_index = animations_map[animation_name].index;
}