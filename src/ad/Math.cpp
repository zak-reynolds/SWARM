#include "ad/Math.h"

gmtl::Vec2f Rotate(gmtl::Vec2f vec, float degrees)
{
    gmtl::Vec2f result;
    float theta = gmtl::Math::deg2Rad(degrees);

    result[0] = vec[0] * gmtl::Math::cos(theta) - vec[1] * gmtl::Math::sin(theta);
    result[1] = vec[0] * gmtl::Math::sin(theta) + vec[1] * gmtl::Math::cos(theta);
    return result;
}

gmtl::Vec2f RotateTowards(gmtl::Vec2f vec, gmtl::Vec2f direction, float amount)
{
    if (gmtl::dot(Rotate(direction, -90), vec) < 0)
    {
        return Rotate(vec, -amount);
    }
    return Rotate(vec, amount);
}

gmtl::Vec2f SetLength(gmtl::Vec2f vec, float length)
{
    gmtl::Vec2f result = gmtl::makeNormal(vec);
    result[0] *= length;
    result[1] *= length;
    return result;
}

float Distance(gmtl::Vec2f a, gmtl::Vec2f b)
{
    gmtl::Vec2f diff = a - b;
    return gmtl::Math::abs(gmtl::length(diff));
}
