#ifndef NORMAL_H
#define NORMAL_H

#include "../spindulysFrontend.h"

#include "integrator.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

class NormalIntegrator final : public Integrator
{
	public:
		NormalIntegrator();

		virtual embree::Vec3f GetPixelColor(Ray& ray,
				PixelSample& pixelSample,
				SceneManager &sceneManager,
				const RenderGlobals& renderGlobals) override;
	private:
};

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // NORMAL_H
