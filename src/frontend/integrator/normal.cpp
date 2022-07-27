#include "normal.h"

#include "../utils/render_helper.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

NormalIntegrator::NormalIntegrator()
{
	_handle = "Normal";
}

embree::Vec3f NormalIntegrator::GetPixelColor(Ray& ray,
		PixelSample& pixelSample,
		SceneManager &sceneManager,
		const RenderGlobals& renderGlobals)
{
	RTCIntersectContext intersectContext;
	rtcInitIntersectContext(&intersectContext);

	rtcIntersect1(sceneManager._scene, &intersectContext, RTCRayHit_(ray));

	// TODO: Hardcoded sky color value for now.
	if (ray.instID == RTC_INVALID_GEOMETRY_ID)
	{
		return embree::Vec3f(0.7, 0.8, 0.9);
	}

	// We setup all the necessary data describing the shading point.
	ShadingPoint shadingPoint(SetupShadingPoint(sceneManager, ray));

	return shadingPoint.N;
}

FRONTEND_NAMESPACE_CLOSE_SCOPE
