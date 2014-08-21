#include "ad/Components.h"
#include "ad/Game.h"

namespace ad {
namespace Logic {

EnemySpawner::EnemySpawner(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::EnemySpawner";
    timer = 3;

    IntervalTime = 2;
}

void EnemySpawner::Update()
{
	timer -= ad::Time.deltaTime();

	if (timer < 0)
	{
        ad::Comps::TransformInitValues ti;
        float screenWidth = ad::Game.GraphicsM()->ScreenSize()[0];
        float xPos = ad::Game.GraphicsM()->CameraX() + (std::rand() % ((int)screenWidth - 50) - ((screenWidth - 50) / 2));
        float yPos = ad::Game.GraphicsM()->CameraY() - ad::Game.GraphicsM()->ScreenSize()[1] / 2 - 100;
        ti.Position = gmtl::Vec3f(xPos, yPos, -1);
        ti.Scale = gmtl::Vec2f(1,1);
        ti.Rotation = 0;
        if (std::rand() % 40 == 30) Game.SceneM()->AddGob("ROOT", "PowerupHealth", ti);
        else if (std::rand() % 10 == 0) Game.SceneM()->AddGob("ROOT", "EnemyMid", ti);
        else Game.SceneM()->AddGob("ROOT", "EnemyWeak", ti);

        timer = std::rand() % IntervalTime;
	}
}

} // namespace Logic
} // namespace ad


