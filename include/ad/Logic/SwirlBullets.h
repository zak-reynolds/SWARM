#ifndef AD_LOGIC_SwirlBullets_H
#define AD_LOGIC_SwirlBullets_H

#include "ad/Components.h"

namespace ad {
namespace Logic {

class SwirlBullets : public ad::Comps::LogicComponent
{
    public:
        SwirlBullets(std::map<std::string, ad::Component*> Requires);
        void Update();
        int speed;
    protected:
    private:
        int rotation;
        int rotation2;
        float timer;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_SwirlBullets_H
