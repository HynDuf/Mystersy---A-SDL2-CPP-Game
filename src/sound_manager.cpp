#include <sound_manager.h>

SoundManager::SoundManager()
{
    bgm = Mix_LoadMUS("sfx-bgm/bgm.wav");
    boss_bgm = Mix_LoadMUS("sfx-bgm/boss_bgm.wav");

    level_up = Mix_LoadWAV("sfx-bgm/level_up.wav");
    monster_appear = Mix_LoadWAV("sfx-bgm/monster_appear.wav");
    Q = Mix_LoadWAV("sfx-bgm/Q_slash.wav");
    E = Mix_LoadWAV("sfx-bgm/E_shield.wav");
    shoot = Mix_LoadWAV("sfx-bgm/shoot.wav");
    slash = Mix_LoadWAV("sfx-bgm/slash.wav");
    player_damaged = Mix_LoadWAV("sfx-bgm/player_damaged.wav");
}
SoundManager::~SoundManager()
{
    Mix_FreeMusic(bgm);
    Mix_FreeMusic(boss_bgm);

    Mix_FreeChunk(level_up);
    Mix_FreeChunk(monster_appear);
    Mix_FreeChunk(Q);
    Mix_FreeChunk(E);
    Mix_FreeChunk(shoot);
    Mix_FreeChunk(slash);
    Mix_FreeChunk(player_damaged);
}
void SoundManager::PlayLevelUp()
{
    Mix_PlayChannel(-1, level_up, 0);
}
void SoundManager::PlayMonsterAppear()
{
    Mix_PlayChannel(-1, monster_appear, 0);
}
void SoundManager::PlayQ()
{
    Mix_PlayChannel(-1, Q, 0);
}
void SoundManager::PlayE()
{
    Mix_PlayChannel(-1, E, 0);
}
void SoundManager::PlayShoot()
{
    Mix_PlayChannel(-1, shoot, 0);
}
void SoundManager::PlaySlash()
{
    Mix_PlayChannel(-1, slash, 0);
}
void SoundManager::PlayPlayerDamaged()
{
    Mix_PlayChannel(-1, player_damaged, 0);
}
void SoundManager::PlayBossBGM()
{
    
    Mix_PlayMusic(boss_bgm, 100);
}
void SoundManager::PlayBGM()
{
    Mix_PlayMusic(bgm, 100);
}