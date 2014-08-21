#ifndef AD_LOGIC_SlowZoom_H
#define AD_LOGIC_SlowZoom_H

#include "ad/Components.h"

namespace ad {
namespace Logic {

class SlowZoom : public ad::Comps::LogicComponent
{
    public:
        SlowZoom(std::map<std::string, ad::Component*> Requires);
        void Update();
    protected:
    private:
        ad::Comps::Transform* myTransform;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_SlowZoom_H
