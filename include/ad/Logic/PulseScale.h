#ifndef AD_LOGIC_PULSESCALE_H
#define AD_LOGIC_PULSESCALE_H

#include <ad/Components/LogicComponent.h>
#include <ad/Components/Transform.h>
#include <ad/Components/Music.h>

namespace ad {
namespace Logic {

class PulseScale : public ad::Comps::LogicComponent
{
    public:
        PulseScale(std::map<std::string, ad::Component*> Requires);
        void Update();
        float GetUpSpeed() { return UpSpeed; }
        void SetUpSpeed(float val) { UpSpeed = val; }
        float GetDownSpeed() { return DownSpeed; }
        void SetDownSpeed(float val) { DownSpeed = val; }
        float GetIntensity() { return Intensity; }
        void SetIntensity(float val) { Intensity = val; }

        float BPM;
    protected:
    private:
        float UpSpeed;
        float DownSpeed;
        float Intensity;
        ad::Comps::Transform* transform;
        ad::Comps::Music* music;
        bool pulsingUp;

        float timer;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_PULSESCALE_H
