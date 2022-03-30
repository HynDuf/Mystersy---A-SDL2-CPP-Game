#pragma once
#include <sprite_component.h>
#include <transform_component.h>
#include <texture_manager.h>

class PlayerSkillE
{
public:
    PlayerSkillE();
    ~PlayerSkillE();
    void Update();
    void Render();
    void ExecuteSkill(int dx, int dy);
    void UpdateHitEnemy();
    bool IsCollide(int x0, int y0, int x1, int y1);
private:

    SDL_Texture *circle_on, *circle_off;
    SpriteComponent *sprite;
    TransformComponent *transform;
    SDL_Rect circle;
    int cooldown; // frames

    int duration; // frames

    bool skill_used;


};

extern PlayerSkillE *player_skill_e;