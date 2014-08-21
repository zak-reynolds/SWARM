#include "ad/Components.h"
#include "ad/Game.h"

namespace ad {
namespace Logic {

LoadingScreen::LoadingScreen(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::LoadingScreen";
    timer = .5;
    trigger = false;
    nextScene = "title.xml";
    #ifdef AD_DEBUG
    nextScene = "test-scene.xml";
    #endif
}

void LoadingScreen::Update()
{
	if (timer <= 0 && !trigger)
	{
	    trigger = true;
	    ad::Game.SceneM()->NextScene(nextScene);
	}
	else
	{
        timer -= ad::Time.deltaTime();
	}
}

} // namespace Logic
} // namespace ad


