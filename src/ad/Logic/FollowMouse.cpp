#include "ad/Components.h"
#include "ad/Game.h"

namespace ad {
namespace Logic {

FollowMouse::FollowMouse(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::FollowMouse";
    reticleTransform = (ad::Comps::Transform*)Requires["THISTransform"];
}

void FollowMouse::Update()
{
	reticleTransform->SetX(Game.EventM()->GetMouseWorldX());
	reticleTransform->SetY(Game.EventM()->GetMouseWorldY());
}

} // namespace Logic
} // namespace ad


