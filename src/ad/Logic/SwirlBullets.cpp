#include "ad/Components.h"
#include "ad/Game.h"

namespace ad {
namespace Logic {

SwirlBullets::SwirlBullets(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::SwirlBullets";
    rotation = 0;
    rotation2 = 0;
    timer = 0;
    speed = 1;
}

void SwirlBullets::Update()
{
    timer -= ad::Time.deltaTime();

    if (timer <= 0)
    {
        if (rotation < 359) rotation += speed;
        else rotation = 0;
        if (rotation2 > 1) rotation2 -= speed;
        else rotation2 = 359;

        // Create bullet
        ad::Comps::TransformInitValues ti;
        gmtl::Vec2f xy = Owner->GetTransform()->GetWorldXY();
        ti.Position = gmtl::Vec3f(xy[0] - 60, xy[1] - 15, 5);
        ti.Scale = gmtl::Vec2f(1,1);
        ti.Rotation = rotation;
        Game.SceneM()->AddGob("ROOT", "EnemyBullet", ti);
        ti.Rotation += 90;
        Game.SceneM()->AddGob("ROOT", "EnemyBullet", ti);
        ti.Rotation += 90;
        Game.SceneM()->AddGob("ROOT", "EnemyBullet", ti);
        ti.Rotation += 90;
        Game.SceneM()->AddGob("ROOT", "EnemyBullet", ti);

        ti.Position = gmtl::Vec3f(xy[0] + 60, xy[1] - 15, 5);
        ti.Rotation = rotation2;
        Game.SceneM()->AddGob("ROOT", "EnemyBullet", ti);
        ti.Rotation += 90;
        Game.SceneM()->AddGob("ROOT", "EnemyBullet", ti);
        ti.Rotation += 90;
        Game.SceneM()->AddGob("ROOT", "EnemyBullet", ti);
        ti.Rotation += 90;
        Game.SceneM()->AddGob("ROOT", "EnemyBullet", ti);

        timer = 1.0/15;
    }
}

} // namespace Logic
} // namespace ad


