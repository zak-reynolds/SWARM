#ifndef AD_LOGIC_DebugText_H
#define AD_LOGIC_DebugText_H

#include "ad/Components.h"

namespace ad {
namespace Logic {

class DebugText : public ad::Comps::LogicComponent
{
    public:
        DebugText(std::map<std::string, ad::Component*> Requires);
        void Update();
    protected:
    private:
        ad::Comps::Text* myText;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_DebugText_H
