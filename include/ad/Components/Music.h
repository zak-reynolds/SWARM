#ifndef AD_COMPONENTS_MUSICCOMPONENT_H
#define AD_COMPONENTS_MUSICCOMPONENT_H

#include <ad/Components/Component.h>
#include <string>

namespace ad {
namespace Comps {

class Music : public ad::Component
{
    public:
        /** Default constructor */
        Music(std::string Music);
        ~Music();
        /** Access Music
         * \return The current value of Music
         */
        std::string GetMusic() { return music; }
        void PlayMusic();
        void PauseMusic();
        void StopMusic();

        void SetMusicPosition(float PositionSecs);
        void SetMusicVolume(float Volume);
        void SetMusicPitch(float Pitch);
        void SetMusicLoop(bool Loop);

        float GetMusicPosition();
    protected:
    private:
        std::string music; //!< Member variable "Music"
};

} // namespace Comps
} // namespace ad

#endif // AD_COMPONENTS_MUSICCOMPONENT_H

