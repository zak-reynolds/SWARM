#ifndef AXOLDRIVE_GAMEOBJECT_H
#define AXOLDRIVE_GAMEOBJECT_H

#include <string>
#include <map>
#include <vector>
#include "ad/Components/Component.h"

namespace ad {

class Component;
namespace Comps { class Transform; }

class Gob
{
    public:
        /** Default constructor */
        Gob(Gob* Parent, std::string Name);
        /** Default destructor */
        ~Gob();
        /** Access name
         * \return The current value of name
         */
        std::string GetName() { return name; }
        /** Access components
         * \return The current value of components
         */
        std::map<std::string, ad::Component*>* Getcomponents() { return &components; }
        bool HasComponent(std::string Type);
        ad::Component* GetComponent(std::string Type);
        ad::Comps::Transform* GetTransform();
        void AddComponent(ad::Component* component);
        /** Access children
         * \return The current value of children
         */
        std::map<std::string, ad::Gob*>* Getchildren() { return &children; }
        /** Access parent
         * \return The current value of parent
         */
        ad::Gob* Getparent() { return parent; }
        ad::Gob* FindChildByName(std::string);
        bool Getenabled() { return enabled; }
        void Setenabled(bool val);
        float GetDepth();

        void Update();

        void AddChild(ad::Gob* Child);
        void RemoveChild(std::string Name);
    protected:
    private:
        std::map<std::string, ad::Component*> components; //!< Member variable "components"
        std::map<std::string, ad::Gob*> children; //!< Member variable "children"
        ad::Gob* parent; //!< Member variable "parent"
        bool enabled; //!< Member variable "enabled"
        std::string name; //!< Member variable "name"
};

} // namespace ad

#endif // AXOLDRIVE_GAMEOBJECT_H
