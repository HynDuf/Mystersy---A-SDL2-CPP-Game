#pragma once

#include <texture_manager.h>
#include <transform_component.h>
class EnemyHealthBar
{
private:
    SDL_Texture *texture;
    TransformComponent *transform;
    int appear_duration;
    int num_partitions;
    int health_each;
public:
    SDL_Rect src_rect, dest_rect;
    
    EnemyHealthBar(TransformComponent *_transform, int _full_health);
    ~EnemyHealthBar();
    void SetTexture(const char *texture_file);
    void SetDestSize(int _w, int _h);
    void Reset(int health);
    void Update(int deltax, int deltay);
    void Draw();
    void Draw(int deltax, int deltay);
};