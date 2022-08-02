#ifndef OCCLUSION_H
#define OCCLUSION_H

#include "../spindulysFrontend.h"

#include "integrator.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

class OcclusionIntegrator final : public Integrator
{
	public:
		OcclusionIntegrator();

		virtual Vec3f GetPixelColor(Ray& ray,
				PixelSample& pixelSample,
				SceneManager &sceneManager,
				const RenderGlobals& renderGlobals) override;
	private:
};

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // OCCLUSION_H
