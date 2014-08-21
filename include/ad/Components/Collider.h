#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "ad/Components/Component.h"
#include <gmtl/gmtl.h>
#include "ad/Containers.h"

namespace ad {
namespace Comps {


class Collider : public ad::Component
{
    public:
        /** Default constructor */
        Collider(gmtl::Vec2f Origin, gmtl::Vec2f Size, int Group, int Radius);
        /** Default destructor */
        ~Collider();

        #ifdef AD_DEBUG_DRAWCOLLIDER
        void Update();
        #endif

        void Clear();

        gmtl::Vec2f GetOrigin() { return origin; }
        gmtl::Vec2f GetSize() { return size; }
        int GetWidth() { return size[0]; }
        int GetHeight() { return size[1]; }
        std::unordered_map<std::string, ad::Gob*> GetContactGobs() { return contactGobs; }
        void AddContactGob(ad::Gob*);
        int GetGroup() { return group; }
        int GetRadius() { return radius; }
    protected:
        gmtl::Vec2f origin;
        gmtl::Vec2f size;
        std::unordered_map<std::string, ad::Gob*> contactGobs;
        int group;
        int radius;
};

}
}
#endif // COLLIDERCOMPONENT_H

