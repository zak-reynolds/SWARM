#ifndef AD_COMPONENTS_LOGICCOMPONENT_H
#define AD_COMPONENTS_LOGICCOMPONENT_H

#include "ad/Components/Component.h"

namespace ad {
namespace Comps {

class LogicComponent : public ad::Component
{
    public:
        /** Default constructor */
        LogicComponent() { }
        virtual void Update() { }
    protected:
    private:
};

} // namespace Comps
} // namespace ad

#endif // AD_COMPONENTS_LOGICCOMPONENT_H
