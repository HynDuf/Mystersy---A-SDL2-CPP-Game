#include <sprite_component.h>

SpriteComponent::SpriteComponent() {}
SpriteComponent::SpriteComponent(const char *texture_file, TransformComponent *_transform, int _h, int _w)
{
    SetTexture(texture_file);
    transform = _transform;
    h = _h;
    w = _w;
}
SpriteComponent::SpriteComponent(const char *texture_file, TransformComponent *_transform, int _h, int _w, int _frames, int _speed)
{
    SetTexture(texture_file);
    transform = _transform;
    frames = _frames;
    speed = _speed;
    h = _h;
    w = _w;
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
    src_rect.h = h;
    src_rect.w = w;
    dest_rect.h = transform->h;
    dest_rect.w = transform->w;

}

// NOTE: Update position of transform first
void SpriteComponent::Update()
{
    dest_rect.x = transform->x;
    dest_rect.y = transform->y;
}
void SpriteComponent::Draw()
{
    TextureManager::Draw(texture, src_rect, dest_rect);
}