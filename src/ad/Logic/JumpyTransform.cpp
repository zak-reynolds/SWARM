#include "ad/Logic/JumpyTransform.h"

namespace ad {
namespace Logic {

JumpyTransform::JumpyTransform(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::JumpyTransform";
    transform = (ad::Comps::Transform*)Requires["THISTransform"];
    homePos += gmtl::Vec2i(transform->GetX(), transform->GetY());
    screenSize += gmtl::Vec2i(800, 600);
    imageSize += gmtl::Vec2i(1600, 1200);
}

void JumpyTransform::Update()
{
    transform->SetX(homePos[0] - (rand() % (imageSize[0] - screenSize[0])));
    transform->SetY(homePos[1] - (rand() % (imageSize[1] - screenSize[1])));
}

} // namespace Logic
} // namespace ad

