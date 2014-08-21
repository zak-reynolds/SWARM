#include "ad/Game.h"
#include "ad/Time.h"
// Check for proper type of wrapper
#ifdef AD_SFML
#include "ad/SFML/GraphicsManager_SFML.h"
#include "ad/SFML/EventManager_SFML.h"
#include "ad/SFML/AudioManager_SFML.h"
#include "ad/SFML/SFML_Helper.h"
#endif

namespace ad
{

// Globally accessible instance
ad::GameClass Game;

ad::GameClass::GameClass()
{
    // Check for proper type of wrappers
    #ifdef AD_SFML
    helper = new SFML_Helper();
    graphicsManager = new ad::Graphics::GraphicsManager_SFML();
    eventManager = new ad::Event::EventManager_SFML();
    sceneManager = new ad::SceneManager();
    soundManager = new ad::Sound::AudioManager_SFML();

    resolution = gmtl::Vec2i(helper->GetmainWindow()->getSize().x, helper->GetmainWindow()->getSize().y);
    #endif

    Score = 0;
    WonGame = false;
    skipRender = true;
}

ad::GameClass::~GameClass()
{

}

int ad::GameClass::Update()
{
    // Update Time
    ad::Time.Update();

    // Update Event
    if (eventManager->Update() == AD_QUITCODE)
    {
        return AD_QUITCODE;
    }

    // Update Game Logic
    sceneManager->UpdateScene();

    // Update Graphics
    if (!skipRender)
        graphicsManager->Update();
    else
        skipRender = false;

    // Update Sound
    soundManager->Update();

    // Everything went normally, return 0
    return AD_NORMALCODE;
}

}
