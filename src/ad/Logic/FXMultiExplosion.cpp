#include "ad/Components.h"
#include "ad/Game.h"

namespace ad {
namespace Logic {

FXMultiExplosion::FXMultiExplosion(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::FXMultiExplosion";
    timer = 0;
    myTransform = (ad::Comps::Transform*)Requires["THISTransform"];
    numExplosions = 0;
}

void FXMultiExplosion::Update()
{
    if (timer < 5)
    {
        timer += ad::Time.deltaTime();
        if (numExplosions == 0)
        {
            ad::Comps::TransformInitValues ti;
            ti.Position = gmtl::Vec3f(0, 0, 1);
            ti.Scale = gmtl::Vec2f(2,2);
            ti.Rotation = 0;
            ad::Game.SceneM()->AddGob(myTransform->GetOwner()->GetName(), "Explosion", ti);
            numExplosions++;
        }
        else if (numExplosions == 1 && timer > 0.2)
        {
            ad::Comps::TransformInitValues ti;
            ti.Position = gmtl::Vec3f(-50, 20, 1);
            ti.Scale = gmtl::Vec2f(1.2,1.2);
            ti.Rotation = 80;
            ad::Game.SceneM()->AddGob(myTransform->GetOwner()->GetName(), "Explosion", ti);
            numExplosions++;
        }
        else if (numExplosions == 2 && timer > 0.8)
        {
            ad::Comps::TransformInitValues ti;
            ti.Position = gmtl::Vec3f(70, -100, 1);
            ti.Scale = gmtl::Vec2f(0.7,0.7);
            ti.Rotation = 250;
            ad::Game.SceneM()->AddGob(myTransform->GetOwner()->GetName(), "Explosion", ti);
            numExplosions++;
        }
        else if (numExplosions == 3 && timer > 1.5)
        {
            ad::Comps::TransformInitValues ti;
            ti.Position = gmtl::Vec3f(10, 20, 1);
            ti.Scale = gmtl::Vec2f(1.25,1.25);
            ti.Rotation = 90;
            ad::Game.SceneM()->AddGob(myTransform->GetOwner()->GetName(), "Explosion", ti);
            numExplosions++;
        }
        else if (numExplosions == 4 && timer > 2.2)
        {
            ad::Comps::TransformInitValues ti;
            ti.Position = gmtl::Vec3f(0, 0, 1);
            ti.Scale = gmtl::Vec2f(3, 3);
            ti.Rotation = 170;
            ad::Game.SceneM()->AddGob(myTransform->GetOwner()->GetName(), "Explosion", ti);
            numExplosions++;
        }
        else if (numExplosions == 5 && timer > 2.9)
        {
            ad::Comps::TransformInitValues ti;
            ti.Position = gmtl::Vec3f(-100, 0, 1);
            ti.Scale = gmtl::Vec2f(1, 1);
            ti.Rotation = 250;
            ad::Game.SceneM()->AddGob(myTransform->GetOwner()->GetName(), "Explosion", ti);
            numExplosions++;
        }
        else if (numExplosions == 6 && timer > 3.4)
        {
            ad::Comps::TransformInitValues ti;
            ti.Position = gmtl::Vec3f(50, 100, 1);
            ti.Scale = gmtl::Vec2f(.8, .8);
            ti.Rotation = 20;
            ad::Game.SceneM()->AddGob(myTransform->GetOwner()->GetName(), "Explosion", ti);
            numExplosions++;
        }
        else if (numExplosions == 7 && timer > 3.9)
        {
            ad::Comps::TransformInitValues ti;
            ti.Position = gmtl::Vec3f(-20, 10, 1);
            ti.Scale = gmtl::Vec2f(1.2, 1.2);
            ti.Rotation = 300;
            ad::Game.SceneM()->AddGob(myTransform->GetOwner()->GetName(), "Explosion", ti);
            numExplosions++;
        }
    }
}

} // namespace Logic
} // namespace ad
