#include "ad/Components/Collider.h"
#include "ad/Game.h"

#ifdef AD_DEBUG
#include "ad/Components/Transform.h"
#endif

namespace ad {
namespace Comps {

Collider::Collider(gmtl::Vec2f Origin, gmtl::Vec2f Size, int Group, int Radius)
{
    Name = "Collider";
    origin = Origin;
    size = Size;
    group = Group;
    radius = Radius;
}

Collider::~Collider()
{
    // Remove reference to this component from SceneManager
    ad::Game.SceneM()->RemoveCollider(Owner->GetName(), group);
}


void Collider::AddContactGob(ad::Gob* Gob)
{
    contactGobs.insert(std::pair<std::string, ad::Gob*>(Gob->GetName(), Gob));
}

//! Called by SceneManager after loop update
void Collider::Clear()
{
    contactGobs.clear();
}

#ifdef AD_DEBUG_DRAWCOLLIDER
void Collider::Update()
{
    ad::Game.GraphicsM()->DrawCircle(
                                     Owner->GetTransform()->GetWorldX(),
                                     Owner->GetTransform()->GetWorldY(),
                                     radius,
                                     0, 255, 0, 128);
}
#endif

}
}

