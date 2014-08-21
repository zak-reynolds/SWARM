#include "ad/Components/Music.h"
#include "ad/I_AudioManager.h"
#include "ad/Game.h"

namespace ad {
namespace Comps {

Music::Music(std::string Music)
{
    this->music = Music;
    Name = "Music";
}

Music::~Music()
{
    StopMusic();
}

void Music::PlayMusic()
{
    ad::Game.AudioM()->PlayMusic(music);
}

void Music::PauseMusic()
{
    ad::Game.AudioM()->PauseMusic(music);
}
void Music::StopMusic()
{
    ad::Game.AudioM()->StopMusic(music);
}

void Music::SetMusicPosition(float PositionSecs)
{
    ad::Game.AudioM()->SetMusicPosition(music, PositionSecs);
}
void Music::SetMusicVolume(float Volume)
{
    ad::Game.AudioM()->SetMusicVolume(music, Volume);
}
void Music::SetMusicPitch(float Pitch)
{
    ad::Game.AudioM()->SetMusicPitch(music, Pitch);
}
void Music::SetMusicLoop(bool Loop)
{
    ad::Game.AudioM()->SetMusicLoop(music, Loop);
}

float Music::GetMusicPosition()
{
    return ad::Game.AudioM()->GetMusicPosition(music);
}

} // namespace Comps
} // namespace ad
