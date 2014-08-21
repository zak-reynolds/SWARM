#ifndef AXOLDRIVE_SOUND_I_SOUNDMANAGER_H
#define AXOLDRIVE_SOUND_I_SOUNDMANAGER_H

#include <string>

namespace ad {
namespace Sound {

/**
Sound Interface:
Needs to play sfx (preloaded) and music (streaming)
*/
class I_AudioManager
{
    public:
        virtual int Initialize() = 0;
        virtual void Update() = 0;
        virtual void Destroy() = 0;

        virtual int PlaySound(std::string File) = 0;
        virtual int PlaySound(std::string File, float Volume, float Pitch, bool Loop) = 0;
        virtual int LoadSound(std::string File) = 0;
        virtual int UnloadSound(std::string File) = 0;

        virtual int PlayMusic(std::string File) = 0;
        virtual int PauseMusic(std::string File) = 0;
        virtual int StopMusic(std::string File) = 0;

        virtual int SetMusicPosition(std::string File, float PositionSecs) = 0;
        virtual int SetMusicVolume(std::string File, float Volume) = 0;
        virtual int SetMusicPitch(std::string File, float Pitch) = 0;
        virtual int SetMusicLoop(std::string File, bool Loop) = 0;
        virtual float GetMusicPosition(std::string File) = 0;

        #ifdef AD_DEBUG
        virtual int GetNumSounds() = 0;
        virtual int GetNumSoundBuffers() = 0;
        #endif
    protected:
    private:
};

} // namespace Graphics
} // namespace ad

#endif // AXOLDRIVE_SOUND_I_SOUNDMANAGER_H

