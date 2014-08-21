#include "ad/Components.h"
#include "ad/Game.h"

namespace ad {
namespace Logic {

FXSmoke::FXSmoke(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::FXSmoke";
    myTransform = (ad::Comps::Transform*)Requires["THISTransform"];
    mySprite = (ad::Comps::Sprite*)Requires["THISSprite"];
}

void FXSmoke::Update()
{
    if (mySprite->Alpha > 0)
    {
        mySprite->Alpha -= ad::Time.deltaTime();
        if (mySprite->Alpha < 0) mySprite->Alpha = 0;
        myTransform->SetScaleX(myTransform->GetScaleX() + ad::Time.deltaTime() / 2);
        myTransform->SetScaleY(myTransform->GetScaleY() + ad::Time.deltaTime() / 2);
        myTransform->SetRotation(myTransform->GetRotation() + ad::Time.deltaTime() * 5);
        myTransform->SetZ(-50);
    }
    else
    {
        ad::Game.SceneM()->RemoveGob(Owner->GetName());
    }
}

} // namespace Logic
} // namespace ad


