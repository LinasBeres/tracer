#include "occlusion.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

OcclusionIntegrator::OcclusionIntegrator()
{
	_handle = "Occlusion";
}

Col3f OcclusionIntegrator::GetPixelColor(Ray& ray,
		PixelSample& pixelSample,
		SceneManager &sceneManager,
		const RenderGlobals& renderGlobals)
{
	// TODO

	return Col3f(1.0f);
}

FRONTEND_NAMESPACE_CLOSE_SCOPE
