#include "ad/Components.h"
#include "ad/Game.h"

namespace ad {
namespace Logic {

PlayMusicOnCreate::PlayMusicOnCreate(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::PlayMusicOnCreate";
    myMusic = (ad::Comps::Music*)Requires["THISMusic"];
    playingMusic = false;
}

void PlayMusicOnCreate::Update()
{
	if (!playingMusic)
	{
	    myMusic->PlayMusic();
	    myMusic->SetMusicLoop(true);
	    playingMusic = true;
	}
}

} // namespace Logic
} // namespace ad


