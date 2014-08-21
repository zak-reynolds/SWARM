#include "ad/Logic/PulseScale.h"
#include "ad/Time.h"

namespace ad {
namespace Logic {

PulseScale::PulseScale(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::PulseScale";
    transform = (ad::Comps::Transform*)Requires["THISTransform"];
    pulsingUp = false;
    UpSpeed = 2.5;
    DownSpeed = -1;
    Intensity = 1.1;

    BPM = 150;

    timer = 0;
    SetEnabled(false);
}

void PulseScale::Update()
{
    if (timer <= 0)
    {
        pulsingUp = true;
        timer += 60 / BPM;
    }

    timer -= ad::Time.deltaTime();

    if (pulsingUp)
    {
        if (transform->GetScaleX() < Intensity) transform->SetScaleX(transform->GetScaleX() + UpSpeed * gmtl::Math::Min<float>(1.0, ad::Time.deltaTime()));
        else pulsingUp = false;
    }
    else
    {
        if (transform->GetScaleX() > 1) transform->SetScaleX(transform->GetScaleX() + DownSpeed * gmtl::Math::Min<float>(1.0, ad::Time.deltaTime()));
        else transform->SetScaleX(1);
    }
    transform->SetScaleY(transform->GetScaleX());
}

} // namespace Logic
} // namespace ad
