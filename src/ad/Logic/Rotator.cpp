#include "ad/Components.h"
#include "ad/Game.h"

namespace ad {
namespace Logic {

Rotator::Rotator(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::Rotator";
    myTransform = (ad::Comps::Transform*)Requires["THISTransform"];
}

void Rotator::Update()
{
    float r = myTransform->GetRotation();
    r += ad::Time.deltaTime() * 50;
    if (r >= 360) r -= 360;
	myTransform->SetRotation(r);
}

} // namespace Logic
} // namespace ad


