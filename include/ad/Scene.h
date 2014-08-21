#ifndef AXOLDRIVE_SCENE_H
#define AXOLDRIVE_SCENE_H

#include "ad/Gameobject.h"

namespace ad {

class Scene
{
    public:
        /** Default constructor */
        Scene(std::string fileName);
        /** Default destructor */
        ~Scene();

        void Update();

        ad::Gob* GetRootGameobject() { return RootGameobject; }
        std::string GetFileName() { return fileName; }
    protected:
    private:
        // Scene Graph
        ad::Gob* RootGameobject;
        std::string fileName;
        // Scene options?
        // List of resources to load
};

} // namespace ad

#endif // AXOLDRIVE_SCENE_H
