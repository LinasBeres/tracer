#ifndef CPU_RAY_H
#define CPU_RAY_H

#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>

#include <spindulys/math/math.h>
#include <spindulys/math/vec3.h>

#include "../spindulysBackendCPU.h"

#include "../camera/cpuCamera.h"

#include <sampling/sampler.h>

#include "../utils/render_helper.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

struct Ray
{
	Vec3f origin;
	float tnear;
	Vec3f direction;
	float time;

	float tfar;
	unsigned int mask;
	unsigned int id;
	unsigned int flags;

	Vec3f Ng;
	float u;
	float v;
	unsigned int primID;
	unsigned int geomID;
	unsigned int instID;

	__forceinline Ray(const Vec3f& origin,
			const Vec3f& direction,
			float tnear = 0.0f,
			float tfar = std::numeric_limits<float>::infinity(),
			float time = 0.0f,
			int mask = -1,
			unsigned int geomID = RTC_INVALID_GEOMETRY_ID,
			unsigned int primID = RTC_INVALID_GEOMETRY_ID,
			unsigned int instID = RTC_INVALID_GEOMETRY_ID)
		: origin(origin),
		tnear(tnear),
		direction(direction),
		time(time),
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
		: tnear(tnear),
		time(time),
		tfar(tfar),
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

		const float pointX((((camera.GetJitter() ? pixelSample.sampler.Uniform1D() : 0.0f) - 0.5f) + pixelSample.pixelX)
				/ (camera.GetResolution().x - 1.0f));
		const float pointY((((camera.GetJitter() ? pixelSample.sampler.Uniform1D() : 0.0f) - 0.5f) + pixelSample.pixelY)
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
			const float randomAngle(2.0f * M_PI * pixelSample.sampler.Uniform1D());
			const float randomRadius(camera.GetAperatureRadius() * sqrt(pixelSample.sampler.Uniform1D()));
			const float apertureX(cos(randomAngle) * randomRadius);
			const float apertureY(sin(randomAngle) * randomRadius);

			aperturePoint = camera.GetPosition() + (axisX * apertureX) + (axisY * apertureY);
		}

		origin = aperturePoint;
		direction = normalize(pointOnPlane - aperturePoint);
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
