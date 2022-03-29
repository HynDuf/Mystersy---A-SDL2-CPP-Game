#include <enemy_health_bar.h>

EnemyHealthBar::EnemyHealthBar(const char *texture_file, TransformComponent *_transform, int _full_health)
{
    SetTexture(texture_file);
    transform = _transform;
    src_rect.x = src_rect.y = 0;
    src_rect.w = 20;
    src_rect.h = 4;
    dest_rect.w = 25;
    dest_rect.h = 7;
    num_partitions = 8;
    appear_duration = 0;
    // ! _full_health has to be divided by num_partitions
    health_each = _full_health / num_partitions;
}
EnemyHealthBar::~EnemyHealthBar()
{
    SDL_DestroyTexture(texture);
}
void EnemyHealthBar::SetTexture(const char *texture_file)
{
    texture = TextureManager::LoadTexture(texture_file);
}

void EnemyHealthBar::Reset(int health)
{
    appear_duration = 70;
    src_rect.y = (8 - ((health + health_each - 1) / health_each)) * src_rect.h;
}

void EnemyHealthBar::Update(int deltax, int deltay)
{
    dest_rect.x = transform->x + deltax;
    dest_rect.y = transform->y + deltay;
}
void EnemyHealthBar::Draw()
{
    TextureManager::Draw(texture, src_rect, dest_rect);
}
void EnemyHealthBar::Draw(int deltax, int deltay)
{
    if (appear_duration > 0)
    {
        appear_duration--;
        dest_rect.x += deltax;
        dest_rect.y += deltay;
        TextureManager::Draw(texture, src_rect, dest_rect);
    }  
}