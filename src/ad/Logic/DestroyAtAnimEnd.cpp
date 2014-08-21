#include "ad/Components.h"
#include "ad/Game.h"

namespace ad {
namespace Logic {

DestroyAtAnimEnd::DestroyAtAnimEnd(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::DestroyAtAnimEnd";
    sc = (ad::Comps::Sprite*)Requires["THISSprite"];
}

void DestroyAtAnimEnd::Update()
{
    if (sc->AnimHasPlayed())
    {
        Game.SceneM()->RemoveGob(Owner->GetName());
        sc->SetEnabled(false);
    }
}

} // namespace Logic
} // namespace ad


