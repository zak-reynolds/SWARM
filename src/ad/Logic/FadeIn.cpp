#include "ad/Components.h"
#include "ad/Game.h"

namespace ad {
namespace Logic {

FadeIn::FadeIn(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::FadeIn";
    mySprite = (ad::Comps::Sprite*)Requires["THISSprite"];
    fadeTime = 16;
    mySprite->Alpha = 0;
}

void FadeIn::Update()
{
    mySprite->Alpha += ad::Time.deltaTime() / fadeTime;
    if (mySprite->Alpha > 1)
        mySprite->Alpha = 1;
}

} // namespace Logic
} // namespace ad


