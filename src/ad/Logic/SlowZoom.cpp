#include "ad/Components.h"
#include "ad/Game.h"

namespace ad {
namespace Logic {

SlowZoom::SlowZoom(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::SlowZoom";
    myTransform = (ad::Comps::Transform*)Requires["THISTransform"];
    myTransform->SetScaleX(.001);
    myTransform->SetScaleY(.001);
}

void SlowZoom::Update()
{
	if (myTransform->GetScaleX() < 1)
	{
	    myTransform->SetScaleX(myTransform->GetScaleX() + ad::Time.deltaTime() * 1.0 / 176);
	    myTransform->SetScaleY(myTransform->GetScaleY() + ad::Time.deltaTime() * 1.0 / 176);
	}
}

} // namespace Logic
} // namespace ad


