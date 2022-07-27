#include "udpt.h"

#include "../shapes/ray.h"


UDPTIntegrator::UDPTIntegrator()
{
	_handle = "UDPT";
}

embree::Vec3f UDPTIntegrator::GetPixelColor(Ray& ray,
		PixelSample& pixelSample,
		SceneManager &sceneManager,
		const RenderGlobals& renderGlobals)
{
	embree::Vec3f colorAccumulation(0.0f);
	embree::Vec3f colorThroughput(1.0f);

	for (int bounce = 0; bounce < renderGlobals.depth; ++bounce)
	{
		RTCIntersectContext intersectContext;
		rtcInitIntersectContext(&intersectContext);

		rtcIntersect1(sceneManager._scene, &intersectContext, RTCRayHit_(ray));

		if (ray.instID == RTC_INVALID_GEOMETRY_ID)
		{
			// TODO: Hardcoded sky color value for now.
			return colorAccumulation += colorThroughput * embree::Vec3f(0.7, 0.8, 0.9);
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
		float directionSign(embree::sign(embree::dot(bsdfSample.wi, shadingPoint.Nw)));
		ray.origin = shadingPoint.P + (directionSign * shadingPoint.error * shadingPoint.Nw);
		ray.direction = bsdfSample.wi;

		// Initializing the new ray.
		ray = Ray(ray.origin, ray.direction, shadingPoint.error);

		colorThroughput = colorThroughput * (bsdfSample.reflectance / bsdfSample.pdf);
	}

	return colorAccumulation;
}
