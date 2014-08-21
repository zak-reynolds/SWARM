#ifndef FXMULTIEXPLOSION_H_INCLUDED
#define FXMULTIEXPLOSION_H_INCLUDED

namespace ad {
namespace Logic {

class FXMultiExplosion : public ad::Comps::LogicComponent
{
    public:
        FXMultiExplosion(std::map<std::string, ad::Component*> Requires);
        void Update();
    protected:
    private:
        ad::Comps::Transform* myTransform;
        float timer;
        int numExplosions;
};

} // namespace Logic
} // namespace ad


#endif // FXMULTIEXPLOSION_H_INCLUDED
