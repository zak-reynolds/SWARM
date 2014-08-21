#include "ad/Components.h"
#include "ad/Game.h"
#include <sstream>
#include "ad/Time.h"

namespace ad {
namespace Logic {

DebugText::DebugText(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::DebugText";
    myText = (ad::Comps::Text*)Requires["THISText"];
    ad::Time.ResetTime();
}

void DebugText::Update()
{
    std::stringstream ss (std::stringstream::in | std::stringstream::out);
    ss << "/// SWARM\n\n\n"
       << "/// SCORE: " << ad::Game.Score << "\n\n\n"
       << "/// TIME: " << ad::Time.GetMinutes() << ":" << ad::Time.GetSeconds() << "\n\n\n"
       << "/// FPS: " << ad::Time.fps();

    #ifdef AD_DEBUG
    ss <<
        "\n\n// # Gobs: " << ad::Game.SceneM()->NumGobs() << "\n\n// # SoundBuffers: " << ad::Game.AudioM()->GetNumSoundBuffers() <<
        "\n\n// # Sounds: " << ad::Game.AudioM()->GetNumSounds() << "\n\n// # Colliders: " << ad::Game.SceneM()->NumColliders() <<
        "\n\n// Resolution: " << ad::Game.GetResolution()[0] << " : " << ad::Game.GetResolution()[1] <<
        "\n\n// Scale Factor: " << 1380.0 / ad::Game.GetResolution()[0];
    #endif

    myText->DisplayText = ss.str();
}

} // namespace Logic
} // namespace ad


