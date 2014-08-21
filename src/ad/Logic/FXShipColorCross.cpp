#include "ad/Components.h"
#include "ad/Game.h"

namespace ad {
namespace Logic {

FXShipColorCross::FXShipColorCross(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::FXShipColorCross";
    deathTimer = std::rand() % 10;
    deathTimer /= 100;
}

void FXShipColorCross::Update()
{
	deathTimer -= ad::Time.deltaTime();
	if (deathTimer <= 0)
	{
	   ad::Game.SceneM()->RemoveGob(Owner->GetName());
	}
}

} // namespace Logic
} // namespace ad


