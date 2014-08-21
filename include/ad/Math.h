#include <gmtl/gmtl.h>
#include <gmtl/VecOps.h>

gmtl::Vec2f Rotate(gmtl::Vec2f vec, float degrees);
gmtl::Vec2f RotateTowards(gmtl::Vec2f vec, gmtl::Vec2f direction, float amount);
gmtl::Vec2f SetLength(gmtl::Vec2f vec, float length);
float Distance(gmtl::Vec2f a, gmtl::Vec2f b);
