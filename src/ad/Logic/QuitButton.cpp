#include "ad/Components.h"
#include "ad/Game.h"

namespace ad {
namespace Logic {

QuitButton::QuitButton(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::QuitButton";
    myTransform = (ad::Comps::Transform*)Requires["THISTransform"];
    myCollider = (ad::Comps::Collider*)Requires["THISCollider"];
}

void QuitButton::Update()
{
    myTransform->SetScaleX(1);
    myTransform->SetScaleY(1);

    // Check if collided with reticle
	std::unordered_map<std::string, ad::Gob*> map = myCollider->GetContactGobs();

	for (auto it = map.begin(); it != map.end(); ++it)
	{
	    // If name is "Reticle"
	    if (it->second->GetName() == "Reticle")
	    {
            // Move/scale/something...
            myTransform->SetScaleX(1.2);
            myTransform->SetScaleY(1.2);

            // Move to next scene
	        if (ad::Game.EventM()->GetKeyPress(ad::Event::MouseLeft))
	        {
	            ad::Game.EventM()->CreateEvent(ad::Event::EventType::WindowClose);
	        }
	    }
	}
}

} // namespace Logic
} // namespace ad


