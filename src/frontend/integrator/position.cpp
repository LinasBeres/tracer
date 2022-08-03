#include "position.h"

#include "../utils/render_helper.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

PositionIntegrator::PositionIntegrator()
{
	_handle = "Position";
}

Col3f PositionIntegrator::GetPixelColor(Ray& ray,
		PixelSample& pixelSample,
		SceneManager &sceneManager,
		const RenderGlobals& renderGlobals)
{
	RTCIntersectContext intersectContext;
	rtcInitIntersectContext(&intersectContext);

	rtcIntersect1(sceneManager._scene, &intersectContext, RTCRayHit_(ray));

	if (ray.instID == RTC_INVALID_GEOMETRY_ID)
	{
		// TODO: Hardcoded sky color value for now.
		return Col3f(0.7, 0.8, 0.9);
	}

	// We setup all the necessary data describing the shading point.
	ShadingPoint shadingPoint(SetupShadingPoint(sceneManager, ray));
	const Vec3f normalizedPoint = normalize(shadingPoint.P);

	return Col3f(normalizedPoint.x, normalizedPoint.y, normalizedPoint.z);
}

FRONTEND_NAMESPACE_CLOSE_SCOPE
