#ifndef AD_LOGIC_LoadingScreen_H
#define AD_LOGIC_LoadingScreen_H

#include "ad/Components.h"

namespace ad {
namespace Logic {

class LoadingScreen : public ad::Comps::LogicComponent
{
    public:
        LoadingScreen(std::map<std::string, ad::Component*> Requires);
        void Update();
    protected:
    private:
        float timer;
        bool trigger;
        std::string nextScene;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_LoadingScreen_H
