#ifndef AD_LOGIC_FXShipColorCross_H
#define AD_LOGIC_FXShipColorCross_H

#include "ad/Components.h"

namespace ad {
namespace Logic {

class FXShipColorCross : public ad::Comps::LogicComponent
{
    public:
        FXShipColorCross(std::map<std::string, ad::Component*> Requires);
        void Update();
    protected:
    private:
        float deathTimer;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_FXShipColorCross_H
