#ifndef DEBUG_H
#define DEBUG_H

#include "integrator.h"


class DebugIntegrator final : public Integrator
{
	public:
		DebugIntegrator();

		virtual embree::Vec3f GetPixelColor(Ray& ray,
				PixelSample& pixelSample,
				SceneManager &sceneManager,
				const RenderGlobals& renderGlobals) override;
	private:
};

#endif // DEBUG_H
