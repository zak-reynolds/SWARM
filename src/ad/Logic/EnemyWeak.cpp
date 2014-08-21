#include "ad/Components.h"
#include "ad/Game.h"

namespace ad {
namespace Logic {

EnemyWeak::EnemyWeak(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::EnemyWeak";
    myTransform = (ad::Comps::Transform*)Requires["THISTransform"];
    myCollider = (ad::Comps::Collider*)Requires["THISCollider"];
    MoveSpeed = 400;

    dead = false;
}

void EnemyWeak::Update()
{
    if (dead) Game.SceneM()->RemoveGob(Owner->GetName());

	myTransform->MoveY(-MoveSpeed * Time.deltaTime());
	if (myTransform->GetY() > 800) dead = true;

	// Check if collided with a bullet
	std::string bullet = "Bullet";
	std::unordered_map<std::string, ad::Gob*> map = myCollider->GetContactGobs();

	for (auto it = map.begin(); it != map.end(); ++it)
	{
	    // If name contains "Bullet"
	    if (it->second->GetName().find(bullet) != std::string::npos && !dead)
	    {
	        // Remove me
	        dead = true;
	        // Remove bullet
	        ad::Game.SceneM()->RemoveGob(it->second->GetName());
	        // Add Explosion
            ad::Comps::TransformInitValues ti;
            ti.Position = gmtl::Vec3f(myTransform->GetPosition());
            ti.Position[2] = 50;
            ti.Scale = gmtl::Vec2f(1,1);
            ti.Rotation = std::rand() % 360;
            Game.SceneM()->AddGob("ROOT", "Explosion", ti);

            Game.Score += 10;
	    }
	    // If name is "Ship"
	    if (it->second->GetName() == "Ship" && !dead)
	    {
	        // Remove me
	        dead = true;
	        // Damage ship
            ((ad::Logic::ShipControl*)Game.SceneM()->GetCurrentRoot()->FindChildByName("Ship")->GetComponent("Logic::ShipControl"))->DamageLevel++;
	        // Add Explosion
            ad::Comps::TransformInitValues ti;
            ti.Position = gmtl::Vec3f(myTransform->GetPosition());
            ti.Position[2] = 50;
            ti.Scale = gmtl::Vec2f(1,1);
            ti.Rotation = std::rand() % 360;
            Game.SceneM()->AddGob("ROOT", "Explosion", ti);
	    }
	}
}

} // namespace Logic
} // namespace ad


