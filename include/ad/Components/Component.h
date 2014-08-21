#ifndef AXOLDRIVE_COMPONENT_H
#define AXOLDRIVE_COMPONENT_H

#include <map>
#include <string>
#include "ad/Gameobject.h"
#include "ad/Math.h"

namespace ad {

class Gob;

class Component
{
    public:
        /** Default constructor */
        Component();
        /** Default destructor */
        virtual ~Component();
        /** Access Owner
         * \return The current value of Owner
         */
        ad::Gob* GetOwner() { return Owner; }
        /** Access OwnerComponents
         * \return The current value of OwnerComponents
         */
        std::map<std::string, ad::Component*>* GetOwnerComponents();
        /** Access Name
         * \return The current value of Name
         */
        ad::Component* GetOwnerComponent(std::string Type);
        std::string GetName() { return Name; }
        void SetOwner(ad::Gob* Owner) { this->Owner = Owner; }
        virtual void Update() { }
        void SetEnabled(bool val) { enabled = val; }
        bool GetEnabled() { return enabled; }
    protected:
        ad::Gob* Owner; //!< Member variable "Owner"
        std::string Name; //!< Member variable "Name"
        bool enabled;
    private:
};

namespace Comps
{

struct TransformInitValues
{
    gmtl::Vec3f Position;
    gmtl::Vec2f Scale;
    float Rotation;
};

}

} // namespace ad

#endif // AXOLDRIVE_COMPONENT_H
