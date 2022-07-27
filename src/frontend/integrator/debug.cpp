#include "debug.h"

#include "../utils/render_helper.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

DebugIntegrator::DebugIntegrator()
{
	_handle = "Debug";
}

embree::Vec3f DebugIntegrator::GetPixelColor(Ray& ray,
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
		return embree::Vec3f(0.7, 0.8, 0.9);
	}

	// We setup all the necessary data describing the shading point.
	ShadingPoint shadingPoint(SetupShadingPoint(sceneManager, ray));

	// We return a color based on the "instID" of the intersected geometry.
	// In Embree, the "primID" correspond to a unique *piece* of geometry, such as a triangle,
	// the "geomID" correspond to a unique ID associated to a geometry we are tracing against in a given sceneManager,
	// and the "instID" is the same as the "geomID", but for instances.
	// In the case of Spindulys, as we adopted the "everything is an instance" philosophy, we are using
	// the "instID" instead of the "geomID", as the root/top-level scene we are tracing against contains only instances,
	// and no actual geometry prototypes.
	// TODO: Using a "parallel_for_each" loop in the SceneManager to generate the Embree geometry
	// means that the IDs will never be the same everytime we run spindulys.
	return embree::Vec3f((static_cast<float>((shadingPoint.instID & 0x000000ff) >>  0)) / 255.0f,
			(static_cast<float>((shadingPoint.instID & 0x0000ff00) >>  8)) / 255.0f,
			(static_cast<float>((shadingPoint.instID & 0x00ff0000) >> 16)) / 255.0f);
}

FRONTEND_NAMESPACE_CLOSE_SCOPE
