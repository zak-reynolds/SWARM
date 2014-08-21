#include "ad/Components.h"
#include "ad/Game.h"

namespace ad {
namespace Logic {

EnemyMid::EnemyMid(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::EnemyMid";
    myTransform = (ad::Comps::Transform*)Requires["THISTransform"];
    myCollider = (ad::Comps::Collider*)Requires["THISCollider"];
    MoveSpeed = 50;

    dead = false;
    timer = 1;
    health = 4;
}

void EnemyMid::Update()
{
    timer -= ad::Time.deltaTime();
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
            // Remove bullet
            ad::Game.SceneM()->RemoveGob(it->second->GetName());

	        if (health > 0) health--;
	        else
	        {
                // Remove me
                dead = true;
                // Add Explosion
                ad::Comps::TransformInitValues ti;
                ti.Position = gmtl::Vec3f(myTransform->GetPosition());
                ti.Position[2] = 50;
                ti.Scale = gmtl::Vec2f(1,1);
                ti.Rotation = std::rand() % 360;
                Game.SceneM()->AddGob("ROOT", "Explosion", ti);

                Game.Score += 50;
	        }
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

	// Fire bullet at player
	if (Game.SceneM()->GetCurrentRoot()->FindChildByName("Ship") != NULL)
	{
        if (timer < 0)
        {
            timer = 1.5;
            // Rotate towards ship
            gmtl::Vec2f dir = Game.SceneM()->GetCurrentRoot()->FindChildByName("Ship")->GetTransform()->GetXY()
                                          - myTransform->GetXY();
            gmtl::normalize(dir);
            int degrees = gmtl::Math::rad2Deg(gmtl::Math::aTan2(dir[1], dir[0])) + 90;
            // Create bullet
            ad::Comps::TransformInitValues ti;
            gmtl::Vec2f xy = Owner->GetTransform()->GetWorldXY();
            ti.Position = gmtl::Vec3f(xy[0], xy[1] + 10, 5);
            ti.Scale = gmtl::Vec2f(1,1);
            ti.Rotation = degrees;
            Game.SceneM()->AddGob("ROOT", "EnemyBullet", ti);
        }
	}
}

} // namespace Logic
} // namespace ad



