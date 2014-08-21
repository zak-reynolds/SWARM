#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include "ad/Components/Component.h"
#include "ad/Components/Transform.h"
#include <gmtl/gmtl.h>

namespace ad {
namespace Comps {


class Text : public ad::Component
{
    public:
        /** Default constructor */
        Text(std::string Font, float Size, gmtl::Vec3i Color);
        /** Default destructor */
        ~Text();

        void Update();

        std::string GetFont() { return Font; }
        // Must run this after initialization!
        void SetTransform();

        std::string DisplayText;
        float Size;
        gmtl::Vec3i Color;
    protected:
        std::string Font; //!< Member variable "Font"
        ad::Comps::Transform* transform;
    private:
};

}
}
#endif // TEXTCOMPONENT_H

