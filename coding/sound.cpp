#include "sound.h"

SoundLoader::SoundLoader()
{
    LoadSounds();
}

void SoundLoader::LoadSounds()
{
    SFX_EnemyDead.loadFromFile("C:\\smfl-project\\SFX\\invaderexplode.ogg");
    SFX_PlayerDead.loadFromFile("C:\\smfl-project\\SFX\\playerexplode.ogg");
    SFX_Shoot.loadFromFile("C:\\smfl-project\\SFX\\shoot.ogg");
}

void SoundLoader::PlaySound(SoundName soundName)
{
    if (soundPlaying) // Check the global soundPlaying variable
    {
        switch (soundName)
        {
            case EnemyDead:
                enemy_sound.setBuffer(SFX_EnemyDead);
                enemy_sound.play();
                break;

            case PlayerDead:
                player_sound.setBuffer(SFX_PlayerDead);
                player_sound.play();
                break;

            case Shoot:
                player_sound.setBuffer(SFX_Shoot);
                player_sound.play();
                break;

            case Stop:
                StopAllSounds();
                break;

            default:
                break;
        }
    }
}

void SoundLoader::StopAllSounds()
{
    player_sound.stop();
    enemy_sound.stop();
}

SoundLoader::~SoundLoader()
{}
