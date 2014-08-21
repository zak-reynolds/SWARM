#include "ad/SceneManager.h"

#include <iostream>
#include <forward_list>
#include <sstream>

#include "ad/Game.h"
#include "ad/Components.h"
#include "ad/Math.h"


namespace ad
{

ad::SceneManager::SceneManager()
{
    currentScene = NULL;
    preloadedScene = NULL;

    std::string sceneToLoad="loading.xml";

    #ifdef AD_DEBUG
    sceneToLoad = "loading.xml";
    #endif

    LoadSceneAndPlay(sceneToLoad);

    runTimeGobCount = 0;
    nextScene = "";

    loadingNextScene = false;
    playNextScene = false;

    // SWARM Optimization
    colliderGroups.insert(std::pair<int, MapColliders>(0, MapColliders()));
    colliderGroups.insert(std::pair<int, MapColliders>(1, MapColliders()));
    colliderGroups.insert(std::pair<int, MapColliders>(2, MapColliders()));
    colliderGroups.insert(std::pair<int, MapColliders>(3, MapColliders()));
}

ad::SceneManager::~SceneManager()
{
    //dtor
}

void ad::SceneManager::UpdateScene()
{
    // Add queued gobs
    while (!queuedGobs.empty())
    {
        queueGobData qgd = queuedGobs.back();
        ad::Gob* newGob = InsertGob(qgd.Parent, qgd.Prefab, qgd.GobCount);

        newGob->GetTransform()->SetPosition(qgd.TIVs.Position);
        newGob->GetTransform()->SetRotation(qgd.TIVs.Rotation);
        newGob->GetTransform()->SetScaleX(qgd.TIVs.Scale[0]);
        newGob->GetTransform()->SetScaleY(qgd.TIVs.Scale[1]);

        queuedGobs.pop_back();
    }
    // Kill dead gobs
    while (!deadGobs.empty())
    {
        if (currentScene->GetRootGameobject()->FindChildByName(deadGobs.back()) != NULL)
        {
            delete currentScene->GetRootGameobject()->FindChildByName(deadGobs.back());
        }
        deadGobs.pop_back();
    }

    // Update Colliders
    //
    // SWARM Optimization: Check group 0v1, 0v2, 1v3 (Player on enemies & their bullets, enemies on player bullets)
    for (auto it = colliderGroups[0].begin(); it != colliderGroups[0].end(); ++it)
    {
        for (auto it2 = colliderGroups[1].begin(); it2 != colliderGroups[1].end(); ++it2)
        {
            // TODO: take into account bboxes instead of simply checking distance
            if (Distance(it->second->GetOwner()->GetTransform()->GetWorldXY(), it2->second->GetOwner()->GetTransform()->GetWorldXY()) <
                it->second->GetRadius() + it2->second->GetRadius())
            {
                it->second->AddContactGob(it2->second->GetOwner());
                it2->second->AddContactGob(it->second->GetOwner());
            }
        }
    }
    for (auto it = colliderGroups[0].begin(); it != colliderGroups[0].end(); ++it)
    {
        for (auto it2 = colliderGroups[2].begin(); it2 != colliderGroups[2].end(); ++it2)
        {
            // TODO: take into account bboxes instead of simply checking distance
            if (Distance(it->second->GetOwner()->GetTransform()->GetWorldXY(), it2->second->GetOwner()->GetTransform()->GetWorldXY()) <
                it->second->GetRadius() + it2->second->GetRadius())
            {
                it->second->AddContactGob(it2->second->GetOwner());
                it2->second->AddContactGob(it->second->GetOwner());
            }
        }
    }
    for (auto it = colliderGroups[1].begin(); it != colliderGroups[1].end(); ++it)
    {
        for (auto it2 = colliderGroups[3].begin(); it2 != colliderGroups[3].end(); ++it2)
        {
            // TODO: take into account bboxes instead of simply checking distance
            if (Distance(it->second->GetOwner()->GetTransform()->GetWorldXY(), it2->second->GetOwner()->GetTransform()->GetWorldXY()) <
                it->second->GetRadius() + it2->second->GetRadius())
            {
                it->second->AddContactGob(it2->second->GetOwner());
                it2->second->AddContactGob(it->second->GetOwner());
            }
        }
    }

    // Update scene
    currentScene->Update();

    // Clear Colliders
    for (auto it = colliderGroups.begin(); it != colliderGroups.end(); ++it)
    {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
        {
            it2->second->Clear();
        }
    }

    // Change scene
    if (nextScene != "" && !loadingNextScene)
    {
        queuedGobs.clear();
        deadGobs.clear();
        for (auto it = colliderGroups.begin(); it != colliderGroups.end(); ++it)
        {
            it->second.clear();
        }
        runTimeGobCount = 0;

        // TODO: Temp, while async code is broken
        LoadSceneAndPlay(nextScene);
        nextScene = "";
        /////////////////////////////////////////

        //loadingNextScene = true;
        //loadingThread = new std::thread(&ad::SceneManager::LoadSceneAsync, this);
    }

    if (playNextScene)
    {
        playNextScene = false;
        PlayNextScene();
    }
}

// This checks all the children of the XML node passed as an argument and adds them into passed-in Gameobject structure
int SceneManager::XML_AnalyzeNode(tinyxml2::XMLElement* thisGobElement, ad::Gob* thisGob, std::string NameSuffix)
{
    tinyxml2::XMLElement* currentElement;
    currentElement = thisGobElement->FirstChildElement();
    bool finished (false);
    while (!finished)
    {
        if (std::strcmp(currentElement->Name(), "G") == 0)
        {
            // Add this Gameobject to thisGob's children
            ad::Gob* currentGob = new ad::Gob(thisGob, currentElement->FindAttribute("name")->Value() + NameSuffix);
            thisGob->AddChild(currentGob);

            #ifdef AD_DEBUG
            std::cout << "Gameobject '" << currentGob->GetName() << "' added to '" << thisGob->GetName() << "'\n";
            #endif

            // Look into currentElement's children for Components and Gameobjects
            XML_AnalyzeNode(currentElement, currentGob, NameSuffix);
        }
        else if (std::strcmp(currentElement->Name(), "C") == 0)
        {
            #ifdef AD_DEBUG
            std::cout <<"    Component '" << currentElement->Attribute("name") << "' added to Gameobject '" << thisGob->GetName() << "'\n";
            #endif

            // Add Component to thisGob
            if (std::strcmp(currentElement->Attribute("name"), "Transform") == 0)
            {
                float x; x = 0;
                currentElement->QueryFloatAttribute("x", &x);
                float y; y = 0;
                currentElement->QueryFloatAttribute("y", &y);
                float z; z = 0;
                currentElement->QueryFloatAttribute("z", &z);
                float sx; sx = 1;
                currentElement->QueryFloatAttribute("sx", &sx);
                float sy; sy = 1;
                currentElement->QueryFloatAttribute("sy", &sy);
                float r; r = 0;
                currentElement->QueryFloatAttribute("r", &r);
                ad::Comps::Transform* tc;
                tc = thisGob->GetTransform();
                tc->SetTransform(x, y, z, sx, sy, r);
                thisGob->AddComponent(tc);

                #ifdef AD_DEBUG
                std::cout <<"      X: " << tc->GetX() << " | Y: " << tc->GetY() << " | Z: " << tc->GetZ() << "\n";
                std::cout <<"      ScaleX: " << tc->GetScaleX() << " | ScaleY: " << tc->GetScaleY() << " | Rotation: " << tc->GetRotation() << "\n";
                #endif
            }
            else if (std::strcmp(currentElement->Attribute("name"), "Sprite") == 0)
            {
                ad::Comps::Sprite* sc;
                float orgX = 0;
                currentElement->QueryFloatAttribute("orgx", &orgX);
                float orgY = 0;
                currentElement->QueryFloatAttribute("orgy", &orgY);
                int numFrames = 1;
                currentElement->QueryIntAttribute("frames", &numFrames);
                int width = -1;
                currentElement->QueryIntAttribute("w", &width);
                int height = -1;
                currentElement->QueryIntAttribute("h", &height);
                float animSpeed = 0;
                currentElement->QueryFloatAttribute("as", &animSpeed);

                sc = new ad::Comps::Sprite(currentElement->Attribute("tex"), gmtl::Vec2f(orgX, orgY), numFrames, gmtl::Vec2i(width, height), animSpeed);
                thisGob->AddComponent(sc);
                sc->SetTransform();

                #ifdef AD_DEBUG
                std::cout << "      Texture: " << currentElement->Attribute("tex") << " | OriginX: " << orgX << " | OriginY: " << orgY << "\n";
                #endif
            }
            else if (std::strcmp(currentElement->Attribute("name"), "Text") == 0)
            {
                ad::Comps::Text* tc;
                float size = 16;
                currentElement->QueryFloatAttribute("size", &size);
                gmtl::Vec3i color(255, 255, 255);
                currentElement->QueryIntAttribute("r", &color[0]);
                currentElement->QueryIntAttribute("g", &color[1]);
                currentElement->QueryIntAttribute("b", &color[2]);

                tc = new ad::Comps::Text(currentElement->Attribute("font"), size, color);
                tc->DisplayText = currentElement->Attribute("text");;

                thisGob->AddComponent(tc);
                tc->SetTransform();
                #ifdef AD_DEBUG
                std::cout << "      Font: " << currentElement->Attribute("font");
                #endif
            }
            else if (std::strcmp(currentElement->Attribute("name"), "Collider") == 0)
            {
                ad::Comps::Collider* cc;
                float orgX = 0;
                currentElement->QueryFloatAttribute("orgx", &orgX);
                float orgY = 0;
                currentElement->QueryFloatAttribute("orgy", &orgY);
                int width = -1;
                currentElement->QueryIntAttribute("w", &width);
                int height = -1;
                currentElement->QueryIntAttribute("h", &height);
                int colliderGroup = 0;
                currentElement->QueryIntAttribute("group", &colliderGroup);
                int radius = 10;
                currentElement->QueryIntAttribute("rad", &radius);

                cc = new ad::Comps::Collider(gmtl::Vec2f(orgX, orgY), gmtl::Vec2f(width, height), colliderGroup, radius);
                thisGob->AddComponent(cc);

                colliderGroups[colliderGroup].insert(std::pair<std::string, ad::Comps::Collider*>(thisGob->GetName(), cc));
            }
            else if (std::strcmp(currentElement->Attribute("name"), "Sound") == 0)
            {
                ad::Comps::Sound* sound;
                sound = new ad::Comps::Sound(currentElement->Attribute("buf"));
                thisGob->AddComponent(sound);

                #ifdef AD_DEBUG
                std::cout <<"      SoundBuffer: " << currentElement->Attribute("buf") << "\n";
                #endif
            }
            else if (std::strcmp(currentElement->Attribute("name"), "Music") == 0)
            {
                ad::Comps::Music* music;
                music = new ad::Comps::Music(currentElement->Attribute("file"));
                thisGob->AddComponent(music);

                #ifdef AD_DEBUG
                std::cout <<"      Music: " << currentElement->Attribute("file") << "\n";
                #endif
            }
            else if (std::strcmp(currentElement->Attribute("name"), "Logic") == 0)
            {
                // Loop through currentElement children, adding each to a map
                std::map<std::string, ad::Component*> requires;
                bool logicFinished (false);
                tinyxml2::XMLElement* logicCurrentElement;
                logicCurrentElement = currentElement->FirstChildElement();
                while (!logicFinished)
                {
                    ad::Gob* compOwner;
                    if (std::strcmp(logicCurrentElement->Attribute("gob"), "THIS") == 0) compOwner = thisGob;
                    else
                    {
                        if (preloadedScene != NULL)
                            compOwner = preloadedScene->GetRootGameobject()->FindChildByName(logicCurrentElement->Attribute("gob"));
                        else
                            compOwner = currentScene->GetRootGameobject()->FindChildByName(logicCurrentElement->Attribute("gob"));
                    }

                    std::string requiresKey = logicCurrentElement->Attribute("gob");
                    requiresKey += logicCurrentElement->Attribute("comp");

                    requires.insert(std::pair<std::string, ad::Component*>(
                        requiresKey,
                        compOwner->GetComponent(logicCurrentElement->Attribute("comp"))));

                    #ifdef AD_DEBUG
                    std::cout << "        Require Added: Gameobject " << logicCurrentElement->Attribute("gob") << "'s component '" << logicCurrentElement->Attribute("comp") << "'\n";
                    #endif

                    if (logicCurrentElement == currentElement->LastChildElement()) logicFinished = true;
                    else logicCurrentElement = logicCurrentElement->NextSiblingElement();
                }
                // TODO: outsource this?
                if (std::strcmp(currentElement->Attribute("sub"), "PulseScale") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::PulseScale(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "DebugKeys") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::DebugKeys(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "DebugText") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::DebugText(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "FloatyTransform") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::FloatyTransform(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "JumpyTransform") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::JumpyTransform(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "ShipControl") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::ShipControl(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "BulletLogic") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::BulletLogic(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "FollowMouse") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::FollowMouse(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "EnemyWeak") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::EnemyWeak(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "EnemySpawner") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::EnemySpawner(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "DestroyAtAnimEnd") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::DestroyAtAnimEnd(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "PlaySoundOnCreate") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::PlaySoundOnCreate(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "FXShipColorCross") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::FXShipColorCross(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "FXSmoke") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::FXSmoke(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "StartButton") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::StartButton(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "PlayMusicOnCreate") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::PlayMusicOnCreate(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "LoadingScreen") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::LoadingScreen(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "SwirlBullets") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::SwirlBullets(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "EnemyBullet") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::EnemyBullet(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "Shield") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::Shield(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "SlowZoom") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::SlowZoom(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "QuitButton") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::QuitButton(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "LevelControl") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::LevelControl(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "EnemyMid") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::EnemyMid(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "PowerupHealth") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::PowerupHealth(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "BossLogic") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::BossLogic(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "Credits") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::Credits(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "Rotator") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::Rotator(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "FadeIn") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::FadeIn(requires));
                }
                else if (std::strcmp(currentElement->Attribute("sub"), "FXMultiExplosion") == 0)
                {
                    thisGob->AddComponent(new ad::Logic::FXMultiExplosion(requires));
                }
                else
                {
                    std::cout << "XML Error: Invalid LogicComponent sub '" << logicCurrentElement->Attribute("sub") << "'\n";
                }
            }
            else if (std::strcmp(currentElement->Attribute("name"), "Camera") == 0)
            {
                thisGob->AddComponent(new ad::Comps::Camera());
            }
            else
            {
                std::cout << "XML Error: Invalid Component name '" << currentElement->Attribute("name") << "'\n";
            }
        }
        if (currentElement == thisGobElement->LastChildElement()) finished = true;
        else currentElement = currentElement->NextSiblingElement();
    }
    return AD_NORMALCODE;
}

// This checks all the children of the XML node passed as an argument and tries to load any resource it comes across
int SceneManager::XML_PreloadResources(tinyxml2::XMLElement* thisGobElement, ad::VectorS* Textures, ad::VectorS* SoundBuffers)
{
    tinyxml2::XMLElement* currentElement;
    currentElement = thisGobElement->FirstChildElement();
    bool finished (false);
    while (!finished)
    {
        if (std::strcmp(currentElement->Name(), "C") == 0)
        {
            if (std::strcmp(currentElement->Attribute("name"), "Sprite") == 0)
            {
                Textures->push_back(currentElement->Attribute("tex"));
            }
            else if (std::strcmp(currentElement->Attribute("name"), "Sound") == 0)
            {
                SoundBuffers->push_back(currentElement->Attribute("buf"));
            }
        }
        else
        {
            // Look into currentElement's children for Components and Gameobjects
            if (currentElement != thisGobElement->LastChildElement()) XML_PreloadResources(currentElement, Textures, SoundBuffers);
        }
        if (currentElement == thisGobElement->LastChildElement()) finished = true;
        else currentElement = currentElement->NextSiblingElement();
    }
    return AD_NORMALCODE;
}


// TODO: Run on another thread?
int ad::SceneManager::LoadScene(std::string File)
{
    tinyxml2::XMLDocument doc;
    std::string Path("Resources/Scene/" + File);
    if (doc.LoadFile(Path.c_str()) == AD_NORMALCODE)
    {
        preloadedScene = new ad::Scene(File);
        XML_AnalyzeNode(doc.RootElement()->FirstChildElement("SceneGraph"), preloadedScene->GetRootGameobject(), "");
        return AD_NORMALCODE;
    }
    else return ERROR_FILENOTFOUND;
}
void ad::SceneManager::LoadSceneAsync()
{
    tinyxml2::XMLDocument doc;
    std::string Path("Resources/Scene/" + nextScene);
    if (doc.LoadFile(Path.c_str()) == AD_NORMALCODE)
    {
        ad::Scene* scene = new ad::Scene(nextScene);
        XML_AnalyzeNode(doc.RootElement()->FirstChildElement("SceneGraph"), scene->GetRootGameobject(), "");

        // Preload Resources
        ad::VectorS* textures = new ad::VectorS();
        ad::VectorS* soundBuffers = new ad::VectorS();
        XML_PreloadResources(doc.RootElement()->FirstChildElement("SceneGraph"), textures, soundBuffers);
        XML_PreloadResources(doc.RootElement()->FirstChildElement("Prefabs"), textures, soundBuffers);
        ad::Game.GraphicsM()->LoadTexturesAsync(textures);
        //ad::Game.AudioM()->LoadSoundBuffersAsync(soundBuffers);

        // TODO: Lock this!
        loadingNextScene = false;
        nextScene = "";
        preloadedScene = scene;
        playNextScene = true;
    }
}

int ad::SceneManager::LoadSceneAndPlay(std::string File)
{
    LoadScene(File);
    PlayNextScene();
    return AD_NORMALCODE;
}

void ad::SceneManager::PlayNextScene()
{
    delete currentScene;
    currentScene = preloadedScene;
    preloadedScene = NULL;
    ad::Game.GraphicsM()->SetCurrentRootGameobject(currentScene->GetRootGameobject());
    // Skip one frame of rendering to allow Gobs to position themselves, since there is only
    // one game loop (rendering and logic are done on the same loop)
    ad::Game.SkipRender();
}

ad::Gob* SceneManager::GetCurrentRoot()
{
    return currentScene->GetRootGameobject();
}

ad::Gob* SceneManager::GetPreloadedRoot()
{
    return preloadedScene->GetRootGameobject();
}

std::string SceneManager::AddGob(std::string Parent, std::string Prefab)
{
    std::stringstream ss (std::stringstream::in | std::stringstream::out);
    ss << "_" << runTimeGobCount;
    runTimeGobCount++;

    queueGobData qgd;
    qgd.Parent = Parent;
    qgd.Prefab = Prefab;
    qgd.GobCount = ss.str();
    queuedGobs.push_back(qgd);

    return Prefab + ss.str();
}
std::string SceneManager::AddGob(std::string Parent, std::string Prefab, ad::Comps::TransformInitValues TIVs)
{
    std::stringstream ss (std::stringstream::in | std::stringstream::out);
    ss << "_" << runTimeGobCount;
    runTimeGobCount++;


    queueGobData qgd;
    qgd.Parent = Parent;
    qgd.Prefab = Prefab;
    qgd.GobCount = ss.str();
    qgd.TIVs = TIVs;
    queuedGobs.push_back(qgd);

    return Prefab + ss.str();
}

ad::Gob* SceneManager::InsertGob(std::string Parent, std::string Prefab, std::string gobCount)
{
    ad::Gob* parent;
    if (std::strcmp(Parent.c_str(), "ROOT") == 0) parent = currentScene->GetRootGameobject();
    else parent = currentScene->GetRootGameobject()->FindChildByName(Parent);

    tinyxml2::XMLDocument doc;
    std::string Path("Resources/Scene/" + currentScene->GetFileName());
    if (doc.LoadFile(Path.c_str()) == AD_NORMALCODE)
    {
        XML_AnalyzeNode(doc.RootElement()->FirstChildElement("Prefabs")->FirstChildElement(Prefab.c_str()), parent, gobCount);
    }
    ad::Gob* newGob = parent->FindChildByName(Prefab + gobCount);

    if (newGob->HasComponent("Sprite")) ad::Game.GraphicsM()->AddSprite(newGob);
    //if (newGob->HasComponent("Collider")) currentColliders.insert(
    //        std::pair<std::string, ad::Comps::Collider*>(
    //                newGob->GetName(), (ad::Comps::Collider*)newGob->GetComponent("Collider")));

    return newGob;
}

//! Queues the Gob for removal at the beginning of the next game loop
void SceneManager::RemoveGob(std::string Name)
{
    deadGobs.push_back(Name);
}

void SceneManager::RemoveCollider(std::string Name, int Group)
{
    colliderGroups[Group].erase(Name);
}

void SceneManager::NextScene(std::string File)
{
    nextScene = File;
}

#ifdef AD_DEBUG
int RecursiveNumGobs(ad::Gob* Gob)
{
    int num = 1;
    for (auto it = Gob->Getchildren()->begin(); it != Gob->Getchildren()->end(); ++it)
    {
        num += RecursiveNumGobs(it->second);
    }
    return num;
}
int SceneManager::NumGobs()
{
    return RecursiveNumGobs(currentScene->GetRootGameobject());
}
int SceneManager::NumColliders()
{
    int n = 0;
    n += colliderGroups[0].size();
    n += colliderGroups[1].size();
    n += colliderGroups[2].size();
    n += colliderGroups[3].size();
    return n;
}
#endif

}
