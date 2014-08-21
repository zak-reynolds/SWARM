#include "ad/Logic/DebugKeys.h"
#include "ad/Game.h"
#include "ad/Components/Transform.h"

namespace ad {
namespace Logic {

DebugKeys::DebugKeys(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::DebugKeys";
    music = (ad::Comps::Music*)Requires["THISMusic"];
}

void DebugKeys::Update()
{
    if (Game.EventM()->GetKeyPress(ad::Event::N)) music->SetMusicPosition(15 * 60);
    if (Game.EventM()->GetKeyPress(ad::Event::BackSpace))
    {
        if (Game.SceneM()->GetcurrentScene()->GetFileName() == "test-scene.xml") Game.SceneM()->NextScene("title.xml");
        else Game.SceneM()->NextScene("test-scene.xml");
    }
    /* Zoom camera
    if (Game.EventM()->GetKeyPress(ad::Event::Up))
    {
        ad::Comps::Transform* camTransform = Game.GraphicsM()->CurrentRootGameobject->FindChildByName("Camera")->GetTransform();
        camTransform->SetScaleX(camTransform->GetScaleX() + 0.1);
        camTransform->SetScaleY(camTransform->GetScaleY() + 0.1);
    }
    if (Game.EventM()->GetKeyPress(ad::Event::Down))
    {
        ad::Comps::Transform* camTransform = Game.GraphicsM()->CurrentRootGameobject->FindChildByName("Camera")->GetTransform();
        camTransform->SetScaleX(camTransform->GetScaleX() - 0.1);
        camTransform->SetScaleY(camTransform->GetScaleY() - 0.1);
    }*/
}

} // namespace Logic
} // namespace ad
