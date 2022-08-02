#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "../spindulysFrontend.h"

#include "integrator.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

class DiffuseIntegrator final : public Integrator
{
	public:
		DiffuseIntegrator();

		virtual Vec3f GetPixelColor(Ray& ray,
				PixelSample& pixelSample,
				SceneManager &sceneManager,
				const RenderGlobals& renderGlobals) override;
	private:
};

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // DIFFUSE_H
