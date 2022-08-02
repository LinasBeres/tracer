#include "udpt.h"

#include "../shapes/ray.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

UDPTIntegrator::UDPTIntegrator()
{
	_handle = "UDPT";
}

Vec3f UDPTIntegrator::GetPixelColor(Ray& ray,
		PixelSample& pixelSample,
		SceneManager &sceneManager,
		const RenderGlobals& renderGlobals)
{
	Vec3f colorAccumulation(0.0f);
	Vec3f colorThroughput(1.0f);

	for (int bounce = 0; bounce < renderGlobals.depth; ++bounce)
	{
		RTCIntersectContext intersectContext;
		rtcInitIntersectContext(&intersectContext);

		rtcIntersect1(sceneManager._scene, &intersectContext, RTCRayHit_(ray));

		if (ray.instID == RTC_INVALID_GEOMETRY_ID)
		{
			// TODO: Hardcoded sky color value for now.
			return colorAccumulation += colorThroughput * Vec3f(0.7, 0.8, 0.9);
		}

		// We setup all the necessary data describing the shading point.
		ShadingPoint shadingPoint(SetupShadingPoint(sceneManager, ray));

		// Sky/Environment Sampling
		// TODO

		// Light Sampling/Next Event Estimation
		// TODO

		// BSDF Sampling
		BSDFSample bsdfSample;
		// TODO: We should use a proper material instead of a BSDF/Lobe directly.
		bsdfSample.wi = diffuseMat.Sample(pixelSample, shadingPoint, bsdfSample);
		bsdfSample.reflectance = diffuseMat.Evaluate(pixelSample, shadingPoint, bsdfSample);

		// Using the world-space normal and the error bias of the shading point , as well as a sign,
		// we apply some form of jitter on the position of the shading point,
		// effectively offsetting the origin of the following ray.
		float directionSign(sign(dot(bsdfSample.wi, shadingPoint.Nw)));
		auto hold = shadingPoint.P + (directionSign * shadingPoint.error * shadingPoint.Nw);
		ray.origin = embree::Vec3f(hold.x, hold.y, hold.z);
		ray.direction = embree::Vec3f(bsdfSample.wi.x, bsdfSample.wi.y, bsdfSample.wi.z);

		// Initializing the new ray.
		ray = Ray(ray.origin, ray.direction, shadingPoint.error);

		colorThroughput = colorThroughput * (bsdfSample.reflectance / bsdfSample.pdf);
	}

	return colorAccumulation;
}

FRONTEND_NAMESPACE_CLOSE_SCOPE
