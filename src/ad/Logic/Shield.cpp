#include "ad/Components.h"
#include "ad/Game.h"

namespace ad {
namespace Logic {

Shield::Shield(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::Shield";
    myCollider = (ad::Comps::Collider*)Requires["THISCollider"];
}

void Shield::Update()
{
	// Check if collided with a bullet
	std::string bullet = "EnemyBullet";
	std::unordered_map<std::string, ad::Gob*> map = myCollider->GetContactGobs();

	for (auto it = map.begin(); it != map.end(); ++it)
	{
	    // If name contains "Bullet"
	    if (it->second->GetName().find(bullet) != std::string::npos)
	    {
	        // Remove bullet
	        ad::Game.SceneM()->RemoveGob(it->second->GetName());
	    }
	}
}

} // namespace Logic
} // namespace ad


