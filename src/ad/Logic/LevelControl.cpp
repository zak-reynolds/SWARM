#include "ad/Components.h"
#include "ad/Game.h"

// Utility function
void SpawnHealth(float x)
{
    ad::Comps::TransformInitValues ti;
    ti.Position = gmtl::Vec3f(400 + x, 300, 1);
    ti.Scale = gmtl::Vec2f(1,1);
    ti.Rotation = 0;
    ad::Game.SceneM()->AddGob("ROOT", "PowerupHealth", ti);
}

namespace ad {
namespace Logic {

LevelControl::LevelControl(std::map<std::string, ad::Component*> Requires)
{
    Name = "Logic::LevelControl";
    musicFirst = (ad::Comps::Music*)Requires["THISMusic"];
    musicBossIntro = (ad::Comps::Music*)Requires["m1Music"];
    musicBoss = (ad::Comps::Music*)Requires["m2Music"];
    musicBossTrans = (ad::Comps::Music*)Requires["m3Music"];
    musicBoss2 = (ad::Comps::Music*)Requires["m4Music"];
    musicPostBoss = (ad::Comps::Music*)Requires["m5Music"];
    stage = 0;
    fadeVolume = 1;
    timer = 5;
    boss = NULL;
    bossstring = "";
    bossProp = "";
    spawnCount = 0;
    endgameTimer = 0;
    dualSpiral = false;
}

void LevelControl::Update()
{
    float musicPos = 0;
	// alpha version progression: gradually increase the number of wasps, while spawning boss in time with the music
	switch (stage)
	{
	    case 0:
        // Camera pulse effect
        Game.SceneM()->GetCurrentRoot()->FindChildByName("Camera")->GetComponent("Logic::PulseScale")->SetEnabled(false);
        // Burst effect
        ad::Game.SceneM()->GetCurrentRoot()->FindChildByName("Burst")->Setenabled(false);
        // Warp effect
        ad::Game.SceneM()->GetCurrentRoot()->FindChildByName("Warp")->Setenabled(false);
	    musicFirst->PlayMusic();
        // Next Stage
	    // DEBUG (Skip to boss)
        //musicFirst->SetMusicPosition(171);
	    stage++;
	    break;
	    case 1:
	    if (musicFirst->GetMusicPosition() > 176) // 2' 56" (176)
	    {
	        musicBossIntro->PlayMusic();
	        // Stop Spawner
	        ad::Game.SceneM()->GetCurrentRoot()->FindChildByName("EnemySpawner")->Setenabled(false);
	        // Next Stage
	        stage++;
	    }
	    break;
	    case 2:
	    {
            musicPos = musicBossIntro->GetMusicPosition();
            ad::Comps::Text* alienText = (ad::Comps::Text*)(Game.SceneM()->GetCurrentRoot()->FindChildByName("AlienTalk")->GetComponent("Text"));

            if (musicPos > 5) alienText->DisplayText = "\n\nAnalyzing...";
            if (musicPos > 6.5) alienText->DisplayText = "\n\nAnalyzing...\nArtificial pattern identified";
            if (musicPos > 10) alienText->DisplayText = "Analyzing...\nArtificial pattern identified\nInsufficient common code...";
            if (musicPos > 12) alienText->DisplayText = "Artificial pattern identified\nInsufficient common code...\nRejecting";
            if (musicPos > 14.2) alienText->DisplayText = "Insufficient common code...\nRejecting\nIntegrating new DNA profile!";
            if (musicPos > 17) alienText->DisplayText = "";

            if ((musicPos > 17.8 && musicPos < 18.8) ||
                (musicPos > 21 && musicPos < 22) ||
                (musicPos > 24.1 && musicPos < 25.1) ||
                (musicPos > 27.2 && musicPos < 28.2))
            {
                if (bossProp == "")
                {
                    // Spawn boss prop
                    ad::Comps::TransformInitValues ti;
                    ti.Position = gmtl::Vec3f(0, -150, 1);
                    ti.Scale = gmtl::Vec2f(0.7,0.7);
                    ti.Rotation = 0;
                    bossProp = ad::Game.SceneM()->AddGob("Camera", "BossProp", ti);
                }
                else
                    ((ad::Logic::FadeIn*)Game.SceneM()->GetCurrentRoot()->FindChildByName(bossProp)->GetComponent("Logic::FadeIn"))->fadeTime = 32;
                ad::Game.SceneM()->GetCurrentRoot()->FindChildByName("Burst")->Setenabled(true);
            }
            else ad::Game.SceneM()->GetCurrentRoot()->FindChildByName("Burst")->Setenabled(false);

            if (musicPos > 32.3) ad::Game.SceneM()->GetCurrentRoot()->FindChildByName("Warp")->Setenabled(true);
            if (musicBossIntro->GetMusicPosition() > 46.3)
            {
                ad::Game.SceneM()->GetCurrentRoot()->FindChildByName("Warp")->GetComponent("Logic::FadeIn")->SetEnabled(false);
                ad::Game.SceneM()->GetCurrentRoot()->FindChildByName("Warp")->GetTransform()->SetZ(-1);
                ((ad::Comps::Sprite*)(ad::Game.SceneM()->GetCurrentRoot()->FindChildByName("Warp")->GetComponent("Sprite")))->Alpha = .1;
                musicBoss->PlayMusic();
                musicBoss->SetMusicLoop(true);
                // Kill boss prop
                ad::Game.SceneM()->RemoveGob(bossProp);
                // Spawn boss
                ad::Comps::TransformInitValues ti;
                ti.Position = gmtl::Vec3f(0, -150, 1);
                ti.Scale = gmtl::Vec2f(1,1);
                ti.Rotation = 0;
                bossstring = ad::Game.SceneM()->AddGob("Camera", "Boss", ti);
                // Next Stage
                stage++;
            }
	    }
	    break;
	    case 3:
        if (boss == NULL) boss = (ad::Logic::BossLogic*)(ad::Game.SceneM()->GetCurrentRoot()->FindChildByName(bossstring)->GetComponent("Logic::BossLogic"));
	    // Check if boss is dead
	    if (musicBoss->GetMusicPosition() > 12.5 && boss->damage > 500)
	    {
	        boss->GetOwner()->Setenabled(false);
            ad::Comps::TransformInitValues ti;
            ti.Position = gmtl::Vec3f(0, -150, 1);
            ti.Scale = gmtl::Vec2f(1,1);
            ti.Rotation = 0;
            bossProp = ad::Game.SceneM()->AddGob("Camera", "BossProp", ti);
            SpawnHealth(0);
            SpawnHealth(-50);
            SpawnHealth(50);
	        musicBoss->StopMusic();
	        musicBossTrans->PlayMusic();
	        // Next Stage
	        stage++;
	    }
	    break;
	    case 4:
        ((ad::Logic::FadeIn*)Game.SceneM()->GetCurrentRoot()->FindChildByName(bossProp)->GetComponent("Logic::FadeIn"))->fadeTime = 4;
	    musicPos = musicBossTrans->GetMusicPosition();
	    if ((musicPos > 17.9 && musicPos < 19) ||
            (musicPos > 21 && musicPos < 22) ||
            (musicPos > 24.1 && musicPos < 25.1) ||
            (musicPos > 27.2 && musicPos < 28.2))
        {
            ad::Game.SceneM()->GetCurrentRoot()->FindChildByName("Burst")->Setenabled(true);
        }
        else ad::Game.SceneM()->GetCurrentRoot()->FindChildByName("Burst")->Setenabled(false);

        if (musicPos < 30.2 &&
            ((ad::Comps::Sprite*)(ad::Game.SceneM()->GetCurrentRoot()->FindChildByName("Warp")->GetComponent("Sprite")))->Alpha > .05)
            ((ad::Comps::Sprite*)(ad::Game.SceneM()->GetCurrentRoot()->FindChildByName("Warp")->GetComponent("Sprite")))->Alpha -= Time.deltaTime();
        if (musicPos > 31.2)
        {
            ad::Game.SceneM()->GetCurrentRoot()->FindChildByName("Warp")->GetComponent("Logic::FadeIn")->SetEnabled(true);
            ad::Game.SceneM()->GetCurrentRoot()->FindChildByName("Warp")->GetTransform()->SetZ(99);
        }

	    if (musicPos > 46.2)
	    {
            ad::Game.SceneM()->GetCurrentRoot()->FindChildByName("Warp")->GetComponent("Logic::FadeIn")->SetEnabled(false);
            ad::Game.SceneM()->GetCurrentRoot()->FindChildByName("Warp")->GetTransform()->SetZ(-1);
            ((ad::Comps::Sprite*)(ad::Game.SceneM()->GetCurrentRoot()->FindChildByName("Warp")->GetComponent("Sprite")))->Alpha = .1;
            ad::Game.SceneM()->RemoveGob(bossProp);
	        boss->GetOwner()->Setenabled(true);
	        musicBoss2->PlayMusic();
	        musicBoss2->SetMusicLoop(true);
	        // Camera pulse effect
	        Game.SceneM()->GetCurrentRoot()->FindChildByName("Camera")->GetComponent("Logic::PulseScale")->SetEnabled(true);
	        // Next Stage
	        stage++;
	    }
	    break;
	    case 5:
	    musicPos = musicBoss2->GetMusicPosition();
	    if (musicPos < 23.7 && !dualSpiral)
	    {
	        ad::Game.SceneM()->GetCurrentRoot()->FindChildByName("EnemySpawner")->Setenabled(true);
	        dualSpiral = true;
	        Game.SceneM()->GetCurrentRoot()->FindChildByName("Camera")->GetComponent("Logic::PulseScale")->SetEnabled(true);
	        ((ad::Logic::SwirlBullets*)(Game.SceneM()->GetCurrentRoot()->FindChildByName(bossstring)->GetComponent("Logic::SwirlBullets")))->speed = 8;
	    }
	    else if (musicPos > 23.7)
	    {
	        ad::Game.SceneM()->GetCurrentRoot()->FindChildByName("EnemySpawner")->Setenabled(false);
	        dualSpiral = false;
	        Game.SceneM()->GetCurrentRoot()->FindChildByName("Camera")->GetComponent("Logic::PulseScale")->SetEnabled(false);
	        ((ad::Comps::Transform*)Game.SceneM()->GetCurrentRoot()->FindChildByName("Camera")->GetComponent("Transform"))->SetScaleXY(1, 1);
	        ((ad::Logic::SwirlBullets*)(Game.SceneM()->GetCurrentRoot()->FindChildByName(bossstring)->GetComponent("Logic::SwirlBullets")))->speed = 1;
	    }

	    // If boss is dead
	    if (boss->damage > 1500)
        {
	        ad::Game.SceneM()->GetCurrentRoot()->FindChildByName("EnemySpawner")->Setenabled(false);
            ad::Game.WonGame = true;
	        ad::Game.SceneM()->RemoveGob(bossstring);
	        // Camera pulse effect
	        Game.SceneM()->GetCurrentRoot()->FindChildByName("Camera")->GetComponent("Logic::PulseScale")->SetEnabled(false);
	        ((ad::Comps::Transform*)Game.SceneM()->GetCurrentRoot()->FindChildByName("Camera")->GetComponent("Transform"))->SetScaleXY(1, 1);
	        // Stop Boss music
            musicBoss2->StopMusic();
            // Create Explosions
            ad::Comps::TransformInitValues ti;
            ti.Position = gmtl::Vec3f(400, 300, -1);
            ti.Scale = gmtl::Vec2f(1,1);
            ti.Rotation = 0;
            Game.SceneM()->AddGob("ROOT", "FXMultiExplosion", ti);
            ti.Position = gmtl::Vec3f(500, 200, -1);
            ti.Scale = gmtl::Vec2f(1,1);
            ti.Rotation = 0;
            Game.SceneM()->AddGob("ROOT", "FXMultiExplosion", ti);
            ti.Position = gmtl::Vec3f(300, 200, -1);
            ti.Scale = gmtl::Vec2f(1,1);
            ti.Rotation = 0;
            Game.SceneM()->AddGob("ROOT", "FXMultiExplosion", ti);
            ti.Position = gmtl::Vec3f(500, 400, -1);
            ti.Scale = gmtl::Vec2f(1,1);
            ti.Rotation = 0;
            Game.SceneM()->AddGob("ROOT", "FXMultiExplosion", ti);
            ti.Position = gmtl::Vec3f(300, 400, -1);
            ti.Scale = gmtl::Vec2f(1,1);
            ti.Rotation = 0;
            Game.SceneM()->AddGob("ROOT", "FXMultiExplosion", ti);

            stage++;
        }
	    break;
	    case 6:
	    timer -= ad::Time.deltaTime();
	    if (timer < 0)
	    {
	        musicPostBoss->PlayMusic();
	        musicPostBoss->SetMusicLoop(true);
	        musicPostBoss->SetMusicPosition(91);
	        // Do credits
            ad::Game.SceneM()->AddGob("Camera", "Credits");
	        // Next Stage
	        stage++;
	    }
	    break;
	    case 7:
	    {
            musicPos = musicPostBoss->GetMusicPosition();
            ad::Comps::TransformInitValues ti;
            float screenWidth = ad::Game.GraphicsM()->ScreenSize()[0];
            float xPos = ad::Game.GraphicsM()->CameraX() + (std::rand() % ((int)screenWidth - 250) - ((screenWidth - 250) / 2));
            float yPos = ad::Game.GraphicsM()->CameraY() - ad::Game.GraphicsM()->ScreenSize()[1] / 2 - 100;
            ti.Position = gmtl::Vec3f(xPos, yPos, -1);
            ti.Scale = gmtl::Vec2f(1,1);
            ti.Rotation = 0;

            if (musicPos > 127 && spawnCount == 0)
            {
                Game.SceneM()->AddGob("ROOT", "EnemyWeak", ti);
                spawnCount++;
            }
            if (musicPos > 130.5 && spawnCount == 1)
            {
                Game.SceneM()->AddGob("ROOT", "EnemyWeak", ti);
                spawnCount++;
            }
            if (musicPos > 133.5 && spawnCount == 2)
            {
                Game.SceneM()->AddGob("ROOT", "EnemyWeak", ti);
                spawnCount++;
            }
            if (musicPos > 163)
            {
                // Next Stage
                stage++;
            }
	    }
	    break;
	    case 8:
	    {
	        // INSANITY
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
	    }
	    break;
	}
}

} // namespace Logic
} // namespace ad


