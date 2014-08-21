#ifndef AD_COMPONENTS_SOUNDCOMPONENT_H
#define AD_COMPONENTS_SOUNDCOMPONENT_H

#include <ad/Components/Component.h>
#include <string>

namespace ad {
namespace Comps {

class Sound : public ad::Component
{
    public:
        /** Default constructor */
        Sound(std::string Sound);
        /** Access Sound
         * \return The current value of Sound
         */
        std::string GetSound() { return sound; }
        int PlaySound();
        int PlaySound(float Volume, float Pitch, bool Loop);
        void StopSound();
    protected:
    private:
        std::string sound; //!< Member variable "sound"
};

} // namespace Comps
} // namespace ad

#endif // AD_COMPONENTS_SOUNDCOMPONENT_H
