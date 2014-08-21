#include "ad/Components.h"
#include "ad/Game.h"

namespace ad {
namespace Logic {

PlaySoundOnCreate::PlaySoundOnCreate(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::PlaySoundOnCreate";
    mySound = (ad::Comps::Sound*)Requires["THISSound"];
    played = false;
}

void PlaySoundOnCreate::Update()
{
	if (!played)
	{
	    float pitch = .8 + (std::rand() % 40 / 100);
	    mySound->PlaySound(40, pitch, false);
	    played = true;
	}
}

} // namespace Logic
} // namespace ad


