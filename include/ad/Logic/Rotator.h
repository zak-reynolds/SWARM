#ifndef AD_LOGIC_Rotator_H
#define AD_LOGIC_Rotator_H

#include "ad/Components.h"

namespace ad {
namespace Logic {

class Rotator : public ad::Comps::LogicComponent
{
    public:
        Rotator(std::map<std::string, ad::Component*> Requires);
        void Update();
    protected:
    private:
        ad::Comps::Transform* myTransform;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_Rotator_H
