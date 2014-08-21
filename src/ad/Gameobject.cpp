#include "ad/Gameobject.h"
#include "ad/Components/Transform.h"
#include <iostream>

namespace ad {

Gob::Gob(ad::Gob* Parent, std::string Name)
{
    parent = Parent;
    name = Name;
    enabled = true;
    AddComponent(new ad::Comps::Transform(0, 0, 0, 1, 1, 0));
}

Gob::~Gob()
{
    // Components
    for (auto it = components.begin(); it != components.end(); ++it)
    {
        delete it->second;
    }
    components.clear();

    // Children
    for (auto it = children.begin(); it != children.end(); ++it)
    {
        delete it->second;
    }
    children.clear();

    // Remove parent's reference
    if (parent != NULL) parent->RemoveChild(name);
}

void Gob::Update()
{
    // Update all Components and children if enabled
    if (enabled)
    {
        // Iterate through components
        for (auto it=components.begin(); it!=components.end(); ++it)
        {
            if (it->second->GetEnabled()) it->second->Update();
        }

        // Iterate through children
        for (auto it = std::begin(children); it != std::end(children); ++it)
        {
            if (it->second->Getenabled()) it->second->Update();
        }
    }
}

void Gob::AddChild(ad::Gob* Child)
{
    children.insert({Child->GetName(), Child});
}

//! Removes child reference. IMPORTANT: Doesn't delete child!
void Gob::RemoveChild(std::string Name)
{
    children.erase(Name);
}

bool Gob::HasComponent(std::string Type)
{
    return components.find(Type) != components.end();
}

void Gob::Setenabled(bool val)
{
    enabled = val;
    // Iterate through children
    for (auto it = std::begin(children); it != std::end(children); ++it)
    {
        it->second->Setenabled(val);
    }
}

void Gob::AddComponent(ad::Component* component)
{
    components.insert(std::pair<std::string, ad::Component*>(component->GetName(), component));
    component->SetOwner(this);
}

ad::Component* Gob::GetComponent(std::string Type)
{
    // Check if component exists
    if (!HasComponent(Type))
    {
        std::cout << "Error: Can't access '" << Type << "' component in " << name << " because it hasn't been added.\n";
        return NULL;
    }
    return components.at(Type);
}

ad::Gob* FindChild(ad::Gob* searchGob, std::string Name)
{
    if (searchGob->Getchildren()->find(Name) != searchGob->Getchildren()->end())
    {
        return searchGob->Getchildren()->find(Name)->second;
    }
    else
    {
        for (auto it = searchGob->Getchildren()->begin(); it != searchGob->Getchildren()->end(); ++it)
        {
            ad::Gob* possibleFound = FindChild(it->second, Name);
            if (possibleFound != NULL)
            {
                return possibleFound;
            }
        }
    }
    return NULL;
}

ad::Gob* Gob::FindChildByName(std::string Name)
{
    return FindChild(this, Name);
}

ad::Comps::Transform* Gob::GetTransform()
{
    return (ad::Comps::Transform*)GetComponent("Transform");
}

float Gob::GetDepth()
{
    return GetTransform()->GetZ();
}


}// namespace ad
