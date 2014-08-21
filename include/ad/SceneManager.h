#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "ad/Scene.h"
#include "ad/Components/Collider.h"
#include "ad/Containers.h"

#include <thread>
#include "tinyxml2.h"

namespace ad
{

typedef std::map<std::string, ad::Comps::Collider*> MapColliders;

class SceneManager
{
    public:
        /** Default constructor */
        SceneManager();
        /** Default destructor */
        virtual ~SceneManager();
        /** Access currentScene
         * \return The current value of currentScene
         */
        ad::Scene* GetcurrentScene() { return currentScene; }
        /** Set currentScene
         * \param val New value to set
         */
        void SetcurrentScene(ad::Scene* val) { currentScene = val; }
        /** Access preloadedScene
         * \return The current value of preloadedScene
         */
        ad::Scene* GetpreloadedScene() { return preloadedScene; }
        /** Set preloadedScene
         * \param val New value to set
         */
        void SetpreloadedScene(ad::Scene* val) { preloadedScene = val; }
        /** Update currentScene */
        void UpdateScene();

        int LoadScene(std::string File);
        void LoadSceneAsync();
        //! Loads and plays given scene (NOTE! Do not call during update loop, use NextScene!)
        int LoadSceneAndPlay(std::string File);
        void NextScene(std::string File);
        void PlayNextScene();

        ad::Gob* GetCurrentRoot();
        ad::Gob* GetPreloadedRoot();
        bool LoadingNextScene() { return loadingNextScene; }

        std::string AddGob(std::string Parent, std::string Prefab);
        std::string AddGob(std::string Parent, std::string Prefab, ad::Comps::TransformInitValues TIVs);
        void RemoveGob(std::string Name);
        void RemoveCollider(std::string Name, int Group);

        #ifdef AD_DEBUG
        int NumGobs();
        int NumColliders();
        #endif
    protected:
        int XML_AnalyzeNode(tinyxml2::XMLElement* thisGobElement, ad::Gob* thisGob, std::string NameSuffix);
        int XML_PreloadResources(tinyxml2::XMLElement* thisGobElement, ad::VectorS* Textures, ad::VectorS* SoundBuffers);
    private:
        ad::Scene* currentScene; //!< Member variable "currentScene"
        ad::Scene* preloadedScene; //!< Member variable "preloadedScene"
        double runTimeGobCount;
        ad::Gob* InsertGob(std::string Parent, std::string Prefab, std::string gobCount);
        struct queueGobData
        {
            std::string Parent;
            std::string Prefab;
            std::string GobCount;
            ad::Comps::TransformInitValues TIVs;
        };
        std::vector<queueGobData> queuedGobs;
        ad::VectorS deadGobs;
        std::string nextScene;
        std::map<int, ad::MapColliders> colliderGroups;

        bool loadingNextScene;
        bool playNextScene;

        #ifndef AD_WINDOWS
        std::thread* loadingThread;
        #endif
};

}
#endif // SCENEMANAGER_H
