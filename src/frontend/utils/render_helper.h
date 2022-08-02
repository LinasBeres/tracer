#ifndef RENDER_HELPER_H
#define RENDER_HELPER_H

#include <spindulys/math/vec2.h>
#include <spindulys/math/vec3.h>

#include "../spindulysFrontend.h"

#include "../shapes/geometry.h"
#include "../sampling/sampler.h"

#include "usd_helper.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

// From Embree 3.x
static constexpr float errorBias = 32.0f * 1.19209e-07f;

enum class IntegratorIds {
	UDPT = 0,
	Diffuse,
	Occlusion,
	Position,
	Normal,
	Debug,
};

struct RenderGlobals
{
	int width = 800;                                   // The width of the image to render.
	int height = 600;                                  // The height of the image to render.
	int depth = 3;                                     // The maximum ray depth, or number of bounces, the renderer can make use of.
	int samples = 1;                                   // Total number of samples per pixel to compute.
	IntegratorIds integratorID = IntegratorIds::UDPT;  // The ID of the integrator currently being used by the renderer.
	bool rayJitter = true;                             // Define whether the camera rays should be jittered or not.
};

struct PixelSample
{
	Sampler& sampler;   // Sampler to use to generate any random numbers in this sample.
	int pixelX = 0;     // Position of the pixel being sampled on the X-axis.
	int pixelY = 0;     // Position of the pixel being sampled on the Y-axis.
	int pixelIdx = 0;   // Index of the pixel being sampled, from 0 to (width * height).
	int samples = 0;    // Total number of samples per pixel to compute.
	int sampleIdx = 0;  // Keep track of how many samples have been computed.

	__forceinline PixelSample(Sampler& sampler, int pixelX, int pixelY, int pixelIdx, int samples, int sampleIdx)
		: sampler(sampler), pixelX(pixelX), pixelY(pixelY), pixelIdx(pixelIdx), samples(samples), sampleIdx(sampleIdx)
	{ }
};

struct ShadingPoint
{
	const std::shared_ptr<Geometry>& geometry;              // Geometry that was intersected by the ray.
	Vec3f V = Vec3f(0.0f);                // View vector of the ray.
	Vec3f P = Vec3f(0.0f);                // World-space position of the shading point.
	Vec3f N = Vec3f(0.0f);                  // Object/Local-space normal of the shading point.
	Vec3f Nw = Vec3f(0.0f);                 // World-space normal of the shading point.
	Vec2f UV = Vec2f(0.0f);               // UV barycentric coordinates of the shading point.
	pxr::GfMatrix3f basis = pxr::GfMatrix3f(1.0f);          // Orthogonal basis of the shading point used for shading computation.
	unsigned int geomID = RTC_INVALID_GEOMETRY_ID;          // Embree Geometry ID of the object the ray hit.
	unsigned int primID = RTC_INVALID_GEOMETRY_ID;          // Embree Primitive ID of the object the ray hit.
	unsigned int instID = RTC_INVALID_GEOMETRY_ID;          // Embree Instance ID of the object the ray hit.
	float error = 0.0f;                                     // Error to take into account when intersecting a primitive.

	__forceinline ShadingPoint(const std::shared_ptr<Geometry>& geometry)
		: geometry(geometry)
	{
	}
};

struct BSDFSample
{
	Vec3f reflectance = Vec3f(0.0f);        // Reflectance of the BSDF sample.
	Vec3f wi = Vec3f(0.0f);               // Direction of the BSDF sample.
	float NdotL = 0.0f;                                     // Dot product of the world-space normal and the exitant/light direction.
	float NdotV = 0.0f;                                     // Dot product of the world-space normal and the incident/view direction.
	float pdf = 0.0f;                                       // PDF of the BSDF sample.
};

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // RENDER_HELPER_H
