#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>
#include <iostream>
#include "globals.h" // Include this to use the global variable

enum SoundName { EnemyDead, PlayerDead, Shoot, Stop };

class SoundLoader
{
private:
    sf::SoundBuffer SFX_PlayerDead, SFX_Shoot, SFX_EnemyDead;
    sf::Sound player_sound, enemy_sound;

public:
    SoundLoader();
    ~SoundLoader();
    void LoadSounds();
    void PlaySound(SoundName soundName); // No soundPlaying parameter
    void StopAllSounds();
};

#endif // SOUND_H
