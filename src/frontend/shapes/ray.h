#ifndef RAY_H
#define RAY_H

#include <embree3/common/math/vec2.h>
#include <embree3/common/math/vec3.h>
#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>

#include <config.h>

#include <camera/camera.h>

#include "../sampling/sampler.h"

#include "../utils/render_helper.h"


struct Ray
{
    embree::Vec3fa origin;
    embree::Vec3fa direction;

    float tfar;
    unsigned int mask;
    unsigned int id;
    unsigned int flags;

    embree::Vec3f Ng;
    float u;
    float v;
    unsigned int primID;
    unsigned int geomID;
    unsigned int instID;

    __forceinline Ray(const embree::Vec3fa& origin,
        const embree::Vec3fa& direction,
        float tnear = 0.0f,
        float tfar = std::numeric_limits<float>::infinity(),
        float time = 0.0f,
        int mask = -1,
        unsigned int geomID = RTC_INVALID_GEOMETRY_ID,
        unsigned int primID = RTC_INVALID_GEOMETRY_ID,
        unsigned int instID = RTC_INVALID_GEOMETRY_ID)
        : origin(origin, tnear),
        direction(direction, time),
        tfar(tfar),
        mask(mask),
        primID(primID),
        geomID(geomID),
        instID(instID)
    {
    }

    __forceinline Ray(const spindulys::Camera& camera,
        const PixelSample& pixelSample,
        float tnear = 0.0f,
        float tfar = std::numeric_limits<float>::infinity(),
        float time = 0.0f,
        int mask = -1,
        unsigned int geomID = RTC_INVALID_GEOMETRY_ID,
        unsigned int primID = RTC_INVALID_GEOMETRY_ID,
        unsigned int instID = RTC_INVALID_GEOMETRY_ID)
        : tfar(tfar),
        mask(mask),
        primID(primID),
        geomID(geomID),
        instID(instID)
    {
        embree::Vec3fa axisX(embree::normalize(embree::cross(camera.GetFront(), camera.GetUp())));
        embree::Vec3fa axisY(embree::normalize(embree::cross(axisX, camera.GetFront())));
        embree::Vec3fa forward(camera.GetPosition() + camera.GetFront());
        embree::Vec3fa vectorX(axisX * std::tan(camera.GetFov().x * 0.5f * (M_PI / 180)));
        embree::Vec3fa vectorY(axisY * std::tan(camera.GetFov().y * -0.5f * (M_PI / 180)));

        float pointX((((camera.GetJitter() ? pixelSample.sampler.Uniform1D() : 0.0f) - 0.5f) + pixelSample.pixelX)
            / (camera.GetResolution().x - 1.0f));
        float pointY((((camera.GetJitter() ? pixelSample.sampler.Uniform1D() : 0.0f) - 0.5f) + pixelSample.pixelY)
            / (camera.GetResolution().y - 1.0f));

        embree::Vec3fa pointOnPlane(camera.GetPosition()
            + ((forward
            + (vectorX * ((2.0f * pointX) - 1.0f))
            + (vectorY * ((2.0f * pointY) - 1.0f))
            - camera.GetPosition())
            * camera.GetFocalDistance()));

        embree::Vec3fa aperturePoint(camera.GetPosition());
        if (camera.GetAperatureRadius() > 0.0f)
        {
            float randomAngle(2.0f * M_PI * pixelSample.sampler.Uniform1D());
            float randomRadius(camera.GetAperatureRadius() * embree::sqrt(pixelSample.sampler.Uniform1D()));
            float apertureX(embree::cos(randomAngle) * randomRadius);
            float apertureY(embree::sin(randomAngle) * randomRadius);

            aperturePoint = camera.GetPosition() + (axisX * apertureX) + (axisY * apertureY);
        }

        origin = embree::Vec3fa(aperturePoint, tnear);
        direction = embree::Vec3fa(embree::normalize(pointOnPlane - aperturePoint), time);
    }
};

__forceinline RTCRay *RTCRay_(Ray& ray)
{
    return (RTCRay *) &ray;
}

__forceinline RTCRayHit *RTCRayHit_(Ray& ray)
{
    return (RTCRayHit *) &ray;
}

#endif // RAY_H
