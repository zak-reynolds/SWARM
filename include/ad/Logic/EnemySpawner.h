#ifndef AD_LOGIC_EnemySpawner_H
#define AD_LOGIC_EnemySpawner_H

#include "ad/Components.h"

namespace ad {
namespace Logic {

class EnemySpawner : public ad::Comps::LogicComponent
{
    public:
        EnemySpawner(std::map<std::string, ad::Component*> Requires);
        void Update();

        int IntervalTime;
    protected:
    private:
        float timer;
};

} // namespace Logic
} // namespace ad

#endif // AD_LOGIC_EnemySpawner_H
