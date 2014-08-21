#ifndef AXOLDRIVE_SOUND_SOUNDMANAGER_SFML
#define AXOLDRIVE_SOUND_SOUNDMANAGER_SFML

#include "ad/I_AudioManager.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <SFML/Audio.hpp>

namespace ad {
namespace Sound {


class AudioManager_SFML : public I_AudioManager
{
    public:
        AudioManager_SFML();
        ~AudioManager_SFML();

        int Initialize();
        void Update();
        void Destroy();

        int PlaySound(std::string File);
        int PlaySound(std::string File, float Volume, float Pitch, bool Loop);
        int LoadSound(std::string File);
        int UnloadSound(std::string File);

        int PlayMusic(std::string File);
        int PauseMusic(std::string File);
        int StopMusic(std::string File);

        int SetMusicPosition(std::string File, float PositionSecs);
        int SetMusicVolume(std::string File, float Volume);
        int SetMusicPitch(std::string File, float Pitch);
        int SetMusicLoop(std::string File, bool Loop);
        float GetMusicPosition(std::string File);

        #ifdef AD_DEBUG
        int GetNumSounds();
        int GetNumSoundBuffers();
        #endif
    protected:
    private:
        std::unordered_map<std::string, sf::SoundBuffer> loadedSoundBuffers;
        std::vector<sf::Sound*> playingSounds;
        std::unordered_map<std::string, sf::Music*> openedMusic;
};

} // namespace Sound
} // namespace ad

#endif // AXOLDRIVE_SOUND_SOUNDMANAGER_SFML

