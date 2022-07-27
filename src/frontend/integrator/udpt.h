#ifndef UPDT_H
#define UPDT_H

#include "../spindulysFrontend.h"

#include "integrator.h"

#include "../bsdf/lambert.h"
#include "../bsdf/orennayar.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

class UDPTIntegrator final : public Integrator
{
	public:
		UDPTIntegrator();

		virtual embree::Vec3f GetPixelColor(Ray& ray,
				PixelSample& pixelSample,
				SceneManager &sceneManager,
				const RenderGlobals& renderGlobals) override;

		// TODO: To remove once we have a proper material system.
		Lambert diffuseMat;
	private:
};

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // UPDT_H
