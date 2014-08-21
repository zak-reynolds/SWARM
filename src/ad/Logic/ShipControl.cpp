#include <sstream>

#include "ad/Components.h"
#include "ad/Game.h"

namespace ad {
namespace Logic {

ShipControl::ShipControl(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::ShipControl";
    topSpeed = 600;
    acceleration = 2400;
    //deceleration = 500;
    deceleration = 2400;
    turnspeed = 500;
    bulletRate = 580;   /*!< Bursts per minute */
    shipTransform = (ad::Comps::Transform*)Requires["THISTransform"];

    bulletCount = 0;
    bulletTimer = 0;

    fxTimer = 0;

    DamageLevel = 0;
}

void ShipControl::Update()
{
    bulletTimer -= ad::Time.deltaTime();
    fxTimer -= ad::Time.deltaTime();

    // Reset target direction
    targetDirection = gmtl::Vec2f(0, 0);

    int boundaryL = ad::Game.GraphicsM()->CameraX() - ad::Game.GraphicsM()->ScreenSize()[0] / 2 + 50;
    int boundaryR = ad::Game.GraphicsM()->CameraX() + ad::Game.GraphicsM()->ScreenSize()[0] / 2 - 50;
    int boundaryT = ad::Game.GraphicsM()->CameraY() - ad::Game.GraphicsM()->ScreenSize()[1] / 2 + 50;
    int boundaryB = ad::Game.GraphicsM()->CameraY() + ad::Game.GraphicsM()->ScreenSize()[1] / 2 - 50;

    if (Game.EventM()->GetKey(Event::W))
    {
        if (shipTransform->GetWorldY() > boundaryT) velocity[1] += acceleration * ad::Time.deltaTime();
    }
    if (Game.EventM()->GetKey(Event::S))
    {
        if (shipTransform->GetWorldY() < boundaryB) velocity[1] -= acceleration * ad::Time.deltaTime();
    }
    if (Game.EventM()->GetKey(Event::A))
    {
        if (shipTransform->GetWorldX() > boundaryL) velocity[0] -= acceleration * ad::Time.deltaTime();
    }
    if (Game.EventM()->GetKey(Event::D))
    {
        if (shipTransform->GetWorldX() < boundaryR) velocity[0] += acceleration * ad::Time.deltaTime();
    }

    // If any are pressed, clamp speed
    if (Game.EventM()->GetKey(Event::W) ||
        Game.EventM()->GetKey(Event::S) ||
        Game.EventM()->GetKey(Event::A) ||
        Game.EventM()->GetKey(Event::D))
    {
        if (gmtl::length(velocity) > topSpeed)
        {
            velocity = SetLength(velocity, topSpeed);
        }
    }
    // If none are pressed, reduce speed
    else
    {
        if (gmtl::length(velocity) - deceleration * ad::Time.deltaTime() >= 0) velocity = SetLength(velocity, gmtl::length(velocity) - deceleration * ad::Time.deltaTime());
        else velocity = gmtl::Vec2f(0, 0);
    }

    // If beyond boundary, clamp speed
    if (shipTransform->GetWorldX() < boundaryL && velocity[0] < 0) velocity[0] = 0;
    if (shipTransform->GetWorldX() > boundaryR && velocity[0] > 0) velocity[0] = 0;
    if (shipTransform->GetWorldY() < boundaryT && velocity[1] > 0) velocity[1] = 0;
    if (shipTransform->GetWorldY() > boundaryB && velocity[1] < 0) velocity[1] = 0;

    // Move Transform
    shipTransform->MoveX(velocity[0] * ad::Time.deltaTime());
    shipTransform->MoveY(velocity[1] * ad::Time.deltaTime());

    // Rotate towards mouse
    gmtl::Vec2f dir = gmtl::Vec2f(Game.EventM()->GetMouseWorldX(), Game.EventM()->GetMouseWorldY()) - gmtl::Vec2f(shipTransform->GetPosition()[0], shipTransform->GetPosition()[1]);
    gmtl::normalize(dir);
    shipTransform->SetRotation(gmtl::Math::rad2Deg(gmtl::Math::aTan2(dir[1], dir[0])) + 90);

    // Create bullet
    if (bulletTimer <= 0)
    {
        if (bulletCount < 3)
        {
            if (Game.EventM()->GetKey(Event::MouseLeft))
            {
                ad::Comps::TransformInitValues ti;

                gmtl::Vec3f front;
                front[0] = gmtl::Math::cos(gmtl::Math::deg2Rad(shipTransform->GetRotation() - 90));
                front[1] = gmtl::Math::sin(gmtl::Math::deg2Rad(shipTransform->GetRotation() - 90));
                front *= 100;

                ti.Position = gmtl::Vec3f(shipTransform->GetPosition() + front);
                ti.Scale = gmtl::Vec2f(1,1);
                ti.Rotation = shipTransform->GetRotation();
                Game.SceneM()->AddGob("ROOT", "Bullet", ti);
            }
            bulletCount++;
            if (bulletCount == 3)
            {
                bulletCount = 0;
                bulletTimer = 1 / (bulletRate / 60);
            }
        }
    }

    // Toggle shield
    if(Game.EventM()->GetKey(Event::MouseLeft))
    {
        Owner->FindChildByName("Shield")->Setenabled(false);

        // Check if collided with a bullet
        std::string bullet = "EnemyBullet";
        std::unordered_map<std::string, ad::Gob*> map = ((ad::Comps::Collider*)Owner->GetComponent("Collider"))->GetContactGobs();

        for (auto it = map.begin(); it != map.end(); ++it)
        {
            // If name contains "Bullet"
            if (it->second->GetName().find(bullet) != std::string::npos)
            {
                // Remove bullet
                ad::Game.SceneM()->RemoveGob(it->second->GetName());
                DamageLevel += .1;
            }
        }

    }
    else
    {
        Owner->FindChildByName("Shield")->Setenabled(true);
    }

    // If damaged
    Owner->FindChildByName("FXShipShocks")->Setenabled(false);

    if (DamageLevel > 0)
    {
        // Color FX
        if (fxTimer <= 0)
        {
            ad::Comps::TransformInitValues ti;
            ti.Position = gmtl::Vec3f(std::rand() % 60 - 30, std::rand() % 20 - 10, -1);
            ti.Scale = gmtl::Vec2f(1,1);
            ti.Rotation = shipTransform->GetRotation();

            if (std::rand() % 2 == 0) ad::Game.SceneM()->AddGob(Owner->GetName(), "FXShipColorCrossR", ti);
            else ad::Game.SceneM()->AddGob(Owner->GetName(), "FXShipColorCrossG", ti);

            fxTimer = (std::rand() % 120) / 100;
        }
        if (DamageLevel > 1)
        {
            if (std::rand() % 3 == 0)
            {
                ad::Comps::TransformInitValues ti;
                ti.Position = gmtl::Vec3f(shipTransform->GetWorldX() + std::rand() % 100 - 50, shipTransform->GetWorldY() + std::rand() % 100 - 50, 2);
                ti.Scale = gmtl::Vec2f(.1,.1);
                ti.Rotation = shipTransform->GetRotation();
                ad::Game.SceneM()->AddGob("ROOT", "FXSmoke", ti);
            }
        }
        if (DamageLevel > 2)
        {
            Owner->FindChildByName("FXShipShocks")->Setenabled(true);
            Owner->FindChildByName("FXShipShocks")->GetTransform()->SetRotation(shipTransform->GetRotation());
        }
        if (DamageLevel > 2)
        {
            // Throttle smoke if FPS is too low
            if (std::rand() % 3 != 0 && ad::Time.fps() > 35)
            {
                ad::Comps::TransformInitValues ti;
                ti.Position = gmtl::Vec3f(shipTransform->GetWorldX() + std::rand() % 100 - 50, shipTransform->GetWorldY() + std::rand() % 100 - 50, -99);
                ti.Scale = gmtl::Vec2f(.1,.1);
                ti.Rotation = shipTransform->GetRotation();
                ad::Game.SceneM()->AddGob("ROOT", "FXSmoke", ti);
            }
        }
        if (DamageLevel > 3)
        {
            // Create destroyed ship facade, end game
            ad::Comps::TransformInitValues ti;
            ti.Position = gmtl::Vec3f(shipTransform->GetWorldX(), shipTransform->GetWorldY(), 0);
            ti.Scale = gmtl::Vec2f(.1,.1);
            ti.Rotation = 0;
            ad::Game.SceneM()->AddGob("ROOT", "FXMultiExplosion", ti);
            ti.Position = gmtl::Vec3f(-400, -400, 110);
            ti.Scale = gmtl::Vec2f(1, 1);
            ti.Rotation = 0;
            ad::Game.SceneM()->AddGob("ROOT", "FXGameOver", ti);

            std::stringstream sstream;

            if (ad::Game.WonGame)
                sstream << "CONGRATULATIONS!\n\nSCORE: ";
            else
                sstream << "GAME OVER\n\nSCORE: ";
            sstream << ad::Game.Score << "\n\nTIME: " << ad::Time.GetMinutes() << ":" << ad::Time.GetSeconds();
            ((ad::Comps::Text*)(ad::Game.SceneM()->GetCurrentRoot()->FindChildByName("GameOverText")->GetComponent("Text")))->DisplayText = sstream.str();
            ad::Game.SceneM()->RemoveGob(Owner->GetName());
        }
    }
}

} // namespace Logic
} // namespace ad

