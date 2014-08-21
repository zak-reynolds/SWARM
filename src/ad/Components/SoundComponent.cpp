#include "ad/Components/Sound.h"
#include "ad/I_AudioManager.h"
#include "ad/Game.h"

namespace ad {
namespace Comps {

Sound::Sound(std::string Sound)
{
    this->sound = Sound;
    Name = "Sound";
}

int Sound::PlaySound()
{
    ad::Game.AudioM()->PlaySound(sound);
    return AD_NORMALCODE;
}
int Sound::PlaySound(float Volume, float Pitch, bool Loop)
{
    ad::Game.AudioM()->PlaySound(sound, Volume, Pitch, Loop);
    return AD_NORMALCODE;
}
void Sound::StopSound() { }

} // namespace Comps
} // namespace ad
