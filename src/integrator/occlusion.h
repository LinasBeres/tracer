#ifndef OCCLUSION_H
#define OCCLUSION_H

#include "integrator.h"


class OcclusionIntegrator final : public Integrator
{
	public:
		OcclusionIntegrator();

		virtual embree::Vec3f GetPixelColor(Ray& ray,
				PixelSample& pixelSample,
				SceneManager &sceneManager,
				const RenderGlobals& renderGlobals) override;
	private:
};

#endif // OCCLUSION_H
