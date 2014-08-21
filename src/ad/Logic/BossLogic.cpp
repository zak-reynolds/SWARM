#include "ad/Components.h"
#include "ad/Game.h"

namespace ad {
namespace Logic {

BossLogic::BossLogic(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::BossLogic";
    myTransform = (ad::Comps::Transform*)Requires["THISTransform"];
    myCollider = (ad::Comps::Collider*)Requires["THISCollider"];

    damage = 0;
}

void BossLogic::Update()
{
    // Check if collided with a bullet
	std::string bullet = "Bullet";
	std::unordered_map<std::string, ad::Gob*> map = myCollider->GetContactGobs();

	for (auto it = map.begin(); it != map.end(); ++it)
	{
	    // If name contains "Bullet"
	    if (it->second->GetName().find(bullet) != std::string::npos)
	    {
	        // Add damage
	        damage++;
	        // Remove bullet
	        ad::Game.SceneM()->RemoveGob(it->second->GetName());
	        // Add Explosion
            ad::Comps::TransformInitValues ti;
            ti.Position = gmtl::Vec3f(it->second->GetTransform()->GetPosition());
            ti.Position[2] = 50;
            ti.Scale = gmtl::Vec2f(.5,.5);
            ti.Rotation = std::rand() % 360;
            Game.SceneM()->AddGob("ROOT", "SilentExplosion", ti);

            Game.Score += 10;
	    }
	    // If name is "Ship"
	    if (it->second->GetName() == "Ship")
	    {
	        // Damage ship
            ((ad::Logic::ShipControl*)Game.SceneM()->GetCurrentRoot()->FindChildByName("Ship")->GetComponent("Logic::ShipControl"))->DamageLevel++;
	    }
	}

	// Check damage and respond

}

} // namespace Logic
} // namespace ad


