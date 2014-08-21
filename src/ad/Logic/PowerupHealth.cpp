#include "ad/Components.h"
#include "ad/Game.h"

namespace ad {
namespace Logic {

PowerupHealth::PowerupHealth(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::PowerupHealth";
    myTransform = (ad::Comps::Transform*)Requires["THISTransform"];
    myCollider = (ad::Comps::Collider*)Requires["THISCollider"];
}

void PowerupHealth::Update()
{
    gmtl::Vec3f velocity;
    velocity[0] = 0;
    velocity[1] = 1;
    velocity *= 100 * Time.deltaTime();
    myTransform->MovePosition(velocity);

    // Destroy when further than 2x the screen width from Camera (center of screen)
    gmtl::Vec2f distance = myTransform->GetXY();
    distance -= Game.GraphicsM()->CameraPosition();
    if (gmtl::length(distance) > Game.GraphicsM()->ScreenSize()[0] * 1.1)
    {
        Game.SceneM()->RemoveGob(Owner->GetName());
    }

    // Check if collided with ship
	std::unordered_map<std::string, ad::Gob*> map = myCollider->GetContactGobs();

	for (auto it = map.begin(); it != map.end(); ++it)
	{
	    // If name is "Ship"
	    if (it->second->GetName() == "Ship")
	    {
	        // Heal ship
	        if (((ad::Logic::ShipControl*)Game.SceneM()->GetCurrentRoot()->FindChildByName("Ship")->GetComponent("Logic::ShipControl"))->DamageLevel > 0)
                ((ad::Logic::ShipControl*)Game.SceneM()->GetCurrentRoot()->FindChildByName("Ship")->GetComponent("Logic::ShipControl"))->DamageLevel--;
	        // Add effect
            ad::Comps::TransformInitValues ti;
            ti.Position = gmtl::Vec3f(myTransform->GetPosition());
            ti.Position[2] = 50;
            ti.Scale = gmtl::Vec2f(2,2);
            ti.Rotation = std::rand() % 360;
            Game.SceneM()->AddGob("ROOT", "PowerupGet", ti);
	        // Remove me
	        Game.SceneM()->RemoveGob(Owner->GetName());
	    }
	}
}

} // namespace Logic
} // namespace ad


