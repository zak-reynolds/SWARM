#include "ad/Components.h"
#include "ad/Game.h"

namespace ad {
namespace Logic {

BulletLogic::BulletLogic(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::BulletLogic";
    transform = (ad::Comps::Transform*)Requires["THISTransform"];
    ((ad::Comps::Sound*)Requires["THISSound"])->PlaySound(10, 1, false);
}

void BulletLogic::Update()
{
    gmtl::Vec3f velocity;
    velocity[0] = gmtl::Math::cos(gmtl::Math::deg2Rad(transform->GetRotation() - 90));
    velocity[1] = gmtl::Math::sin(gmtl::Math::deg2Rad(transform->GetRotation() - 90));
    velocity *= 800 * Time.deltaTime();
    transform->MovePosition(velocity);

    // Destroy when further than 2x the screen width from Camera (center of screen)
    gmtl::Vec2f distance = transform->GetXY();
    distance -= Game.GraphicsM()->CameraPosition();
    if (gmtl::length(distance) > Game.GraphicsM()->ScreenSize()[0] * 1.1)
    {
        Game.SceneM()->RemoveGob(Owner->GetName());
    }
}

} // namespace Logic
} // namespace ad


