#ifndef AD_LOGIC_StartButton_H
#define AD_LOGIC_StartButton_H

#include "ad/Components.h"

namespace ad {
namespace Logic {

class StartButton : public ad::Comps::LogicComponent
{
    public:
        StartButton(std::map<std::string, ad::Component*> Requires);
        void Update();
    protected:
    private:
        ad::Comps::Transform* myTransform;
        ad::Comps::Collider* myCollider;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_StartButton_H
