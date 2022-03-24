#pragma once
#include <sprite_component.h>
#include <transform_component.h>
#include <texture_manager.h>

class PlayerSkillQ
{
public:
    PlayerSkillQ();
    ~PlayerSkillQ();
    void Update();
    void Render();
    void ExecuteSkill(int dx, int dy);
    bool CollideEnemy();
private:

    SDL_Texture *circle_on, *circle_off;
    SpriteComponent *sprite;
    TransformComponent *transform;
    SDL_Rect circle;
    int cooldown; // frames

    int duration; // frames

    bool skill_used;


};

extern PlayerSkillQ *player_skill_q;