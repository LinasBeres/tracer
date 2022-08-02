#ifndef COLOR_HELPER_H
#define COLOR_HELPER_H

#include <spindulys/math/vec3.h>

#include "../spindulysFrontend.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

inline float Clamp(float colorChannel)
{
    return colorChannel < 0.0f ? 0.0f : colorChannel > 1.0f ? 1.0f : colorChannel;
}

inline Vec3f Clamp(const Vec3f &color)
{
    return Vec3f(Clamp(color.x),
        Clamp(color.y),
        Clamp(color.z));
}

inline float ToSRGB(float colorChannel)
{
    return std::pow(colorChannel, 1.0f / 2.2f);
}

inline Vec3f ToSRGB(const Vec3f &color)
{
    return Vec3f(ToSRGB(color.x),
        ToSRGB(color.y),
        ToSRGB(color.z));
}

inline float ToLinear(float colorChannel)
{
    return std::pow(colorChannel, 2.2f);
}

inline Vec3f ToLinear(const Vec3f &color)
{
    return Vec3f(ToLinear(color.x),
        ToLinear(color.y),
        ToLinear(color.z));
}

inline int ToRGB(float colorChannel)
{
    return static_cast<int>(Clamp(colorChannel) * 255);
}

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // COLOR_HELPER_H
