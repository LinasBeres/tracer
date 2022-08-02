#ifndef RAY_H
#define RAY_H

#include <embree3/common/math/vec2.h>
#include <embree3/common/math/vec3.h>
#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>

#include <spindulys/math/vec3.h>

#include "../spindulysFrontend.h"

#include "../camera/camera.h"

#include "../sampling/sampler.h"

#include "../utils/render_helper.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

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

	__forceinline Ray(const Camera& camera,
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
		const Vec3f axisX(normalize(cross(camera.GetFront(), camera.GetUp())));
		const Vec3f axisY(normalize(cross(axisX, camera.GetFront())));
		const Vec3f forward(camera.GetPosition() + camera.GetFront());
		const Vec3f vectorX(axisX * tan(camera.GetFov().x * 0.5f * (float(M_PI) / 180.f)));
		const Vec3f vectorY(axisY * tan(camera.GetFov().y * -0.5f * (float(M_PI) / 180.f)));

		float pointX((((camera.GetJitter() ? pixelSample.sampler.Uniform1D() : 0.0f) - 0.5f) + pixelSample.pixelX)
				/ (camera.GetResolution().x - 1.0f));
		float pointY((((camera.GetJitter() ? pixelSample.sampler.Uniform1D() : 0.0f) - 0.5f) + pixelSample.pixelY)
				/ (camera.GetResolution().y - 1.0f));

		const Vec3f pointOnPlane(camera.GetPosition()
				+ ((forward
						+ (vectorX * ((2.0f * pointX) - 1.0f))
						+ (vectorY * ((2.0f * pointY) - 1.0f))
						- camera.GetPosition())
					* camera.GetFocalDistance()));

		Vec3f aperturePoint(camera.GetPosition());
		if (camera.GetAperatureRadius() > 0.0f)
		{
			float randomAngle(2.0f * M_PI * pixelSample.sampler.Uniform1D());
			float randomRadius(camera.GetAperatureRadius() * embree::sqrt(pixelSample.sampler.Uniform1D()));
			float apertureX(embree::cos(randomAngle) * randomRadius);
			float apertureY(embree::sin(randomAngle) * randomRadius);

			aperturePoint = camera.GetPosition() + (axisX * apertureX) + (axisY * apertureY);
		}

		origin = embree::Vec3fa(embree::Vec3fa(aperturePoint.x, aperturePoint.y, aperturePoint.z), tnear);
		const Vec3f hold = normalize(pointOnPlane - aperturePoint);
		direction = embree::Vec3fa(embree::Vec3fa(hold.x, hold.y, hold.z), time);
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

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // RAY_H
