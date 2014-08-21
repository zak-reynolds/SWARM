#include "ad/Logic/FloatyTransform.h"
#include "ad/Time.h"

namespace ad {
namespace Logic {

FloatyTransform::FloatyTransform(std::map<std::string, ad::Component*> Requires)
{
    intensity = 0.3 * 60;
    constrain = 20;
    turnspeed = 1 * 60;
    velocity[0] = intensity;
    resetdistance = 5;

    Name = "Logic::FloatyTransform";
    transform = (ad::Comps::Transform*)Requires["THISTransform"];
    homePos += gmtl::Vec2f(transform->GetX(), transform->GetY());
    targetPos += gmtl::Vec2f(homePos[0] + (rand() % constrain * 2 - constrain / 2), homePos[1] + (rand() % constrain * 2 - constrain / 2));
    //targetScale = .95 + (rand() % 10) / 100;
    lastFramePos = homePos;
}

void FloatyTransform::Update()
{
    // Technique: Pick a random point within constraints (sphere with radius "constrain") of targetPos
    //            Set a low velocity and rotation speed and move towards point, setting new point on arrival

    gmtl::Vec2f pos2target;
    pos2target = targetPos - lastFramePos;

    // If something else moved the transform, account for it
    if ((int)transform->GetX() != (int)lastFramePos[0] || (int)transform->GetY() != (int)lastFramePos[1])
    {
        homePos += gmtl::Vec2f(transform->GetX() + lastFramePos[0], transform->GetY() + lastFramePos[1]);
    }

    // Reset targetPos if close
    if (gmtl::length(pos2target) < resetdistance)
    {
        targetPos[0] = 0;
        targetPos[1] = 0;
        targetPos += gmtl::Vec2f(homePos[0] + (rand() % constrain * 2 - constrain / 2), homePos[1] + (rand() % constrain * 2 - constrain / 2));
        //targetScale = .95 + (rand() % 10) / 100;
    }

    // Adjust velocity direction
    if (gmtl::dot(Rotate(pos2target, -90), velocity) < 0)
    {
        velocity = Rotate(velocity, -turnspeed * ad::Time.deltaTime());
    }
    else
    {
        velocity = Rotate(velocity, turnspeed * ad::Time.deltaTime());
    }

    // Update transform
    transform->SetX(transform->GetX() + velocity[0] * ad::Time.deltaTime());
    transform->SetY(transform->GetY() + velocity[1] * ad::Time.deltaTime());
    //transform->SetScaleX(transform->GetScaleX() + (targetScale - transform->GetScaleX()) / 2);
    //transform->SetScaleY(transform->GetScaleY() + (targetScale - transform->GetScaleY()) / 2);

    lastFramePos[0] = transform->GetX();
    lastFramePos[1] = transform->GetY();
}

} // namespace Logic
} // namespace ad
