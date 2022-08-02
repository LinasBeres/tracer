#include "integrator.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

Integrator::Integrator()
{
}

ShadingPoint Integrator::SetupShadingPoint(SceneManager &sceneManager,
		const Ray& ray)
{
	ShadingPoint shadingPoint(sceneManager._sceneGeom[ray.instID]);

	shadingPoint.V = -Vec3f(ray.direction.x, ray.direction.y, ray.direction.z);
	auto hold = ray.origin + ray.tfar * ray.direction;
	shadingPoint.P = Vec3f(hold.x, hold.y, hold.z);

	// TODO: Use the normals primvar if available (for smooth normals).
	shadingPoint.N = normalize(Vec3f(ray.Ng.x, ray.Ng.y, ray.Ng.z));

	// Object to world space normal conversion.
	Vec3f normalWorld(spindulys::USDToEmbreeMatrixMultiply(shadingPoint.N, shadingPoint.geometry->GetTransform()));
	// We make the normal faceforwarding.
	shadingPoint.Nw = normalize(dot(shadingPoint.V, normalWorld) < 0.0f ? -normalWorld : normalWorld);
	shadingPoint.UV = Vec2f(ray.u, ray.v);

	// We compute the tangent and bitangent from the normal.
	// TODO: Use the tangents primvar if available (for smooth tangents).
	Vec3f tangent(0.0f);
	Vec3f bitangent(0.0f);

	if(abs(shadingPoint.Nw.x) > abs(shadingPoint.Nw.y))
		tangent = Vec3f(-shadingPoint.Nw.z, 0.0f, shadingPoint.Nw.x) *
			(1.0f / sqrt(shadingPoint.Nw.x * shadingPoint.Nw.x +
													 shadingPoint.Nw.y * shadingPoint.Nw.y +
													 shadingPoint.Nw.z * shadingPoint.Nw.z));
	else
		tangent = Vec3f(0.0f, shadingPoint.Nw.z, -shadingPoint.Nw.y) *
			(1.0f / sqrt(shadingPoint.Nw.x * shadingPoint.Nw.x +
													 shadingPoint.Nw.y * shadingPoint.Nw.y +
													 shadingPoint.Nw.z * shadingPoint.Nw.z));

	bitangent = normalize(cross(shadingPoint.Nw, tangent));

	// We setup an orthogonal basis out of the normal, tangent and bitangent.
	shadingPoint.basis = pxr::GfMatrix3f(tangent.x, tangent.y, tangent.z,
			shadingPoint.Nw.x, shadingPoint.Nw.y, shadingPoint.Nw.z,
			bitangent.x, bitangent.y, bitangent.z);

	// We setup the last miscellaneous data of the shading point.
	shadingPoint.geomID = ray.geomID;
	shadingPoint.primID = ray.primID;
	shadingPoint.instID = ray.instID;
	shadingPoint.error = errorBias * std::max(
			std::max(std::abs(shadingPoint.P.x), abs(shadingPoint.P.y)),
			std::max(std::abs(shadingPoint.P.z), ray.tfar));

	return shadingPoint;
}

FRONTEND_NAMESPACE_CLOSE_SCOPE
