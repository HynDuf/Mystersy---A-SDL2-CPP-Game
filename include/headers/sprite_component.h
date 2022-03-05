#pragma once

#include <texture_manager.h>
#include <transform_component.h>

class SpriteComponent
{
private:

    SDL_Texture *texture;
    TransformComponent *transform;
    SDL_Rect src_rect, dest_rect;

    bool animated = false;
    int frames = 0;
    int speed = 100;
    int h, w;
public:
    SpriteComponent();
    SpriteComponent(const char *texture_file, TransformComponent *_transform, int _h, int _w);
    SpriteComponent(const char *texture_file, TransformComponent *_transform, int _h, int _w, int _frames, int _speed);
    ~SpriteComponent();
    void SetTexture(const char *texture_file);
    void Init();
    void Update();
    void Draw();
};