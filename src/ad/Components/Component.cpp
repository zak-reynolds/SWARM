#include "ad/Components/Component.h"

namespace ad {

Component::Component()
{
    enabled = true;
}

Component::~Component()
{
    //dtor
}

std::map<std::string, ad::Component*>* Component::GetOwnerComponents() { return Owner->Getcomponents(); }

ad::Component* Component::GetOwnerComponent(std::string Type) { return Owner->GetComponent(Type); }
} // namespace ad
