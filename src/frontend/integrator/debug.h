#ifndef DEBUG_H
#define DEBUG_H

#include "../spindulysFrontend.h"

#include "integrator.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

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

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // DEBUG_H
