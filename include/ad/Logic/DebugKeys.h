#ifndef AD_LOGIC_DEBUGKEYS_H
#define AD_LOGIC_DEBUGKEYS_H

#include <ad/Components/LogicComponent.h>
#include "ad/Components/Music.h"

namespace ad {
namespace Logic {

class DebugKeys : public ad::Comps::LogicComponent
{
    public:
        DebugKeys(std::map<std::string, ad::Component*> Requires);
        void Update();
    protected:
    private:
        ad::Comps::Music* music;
        bool musicPlaying;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_DEBUGKEYS_H
