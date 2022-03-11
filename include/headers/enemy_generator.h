#pragma once
#include <enemy_manager.h>
#include <vector>
class EnemyGenerator 
{
public:
    EnemyGenerator(const char *texture_file);
    ~EnemyGenerator();
    void AddNewEnemy(int x, int y);
    void Update();
    void Render();
    std::vector<EnemyManager*> enemy_container;

private:
    const int MAX_ENEMY = 50;
    int generator_interval;
    const char *texture;

};
extern EnemyGenerator *enemy_generator;