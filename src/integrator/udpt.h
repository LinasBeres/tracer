#ifndef UPDT_H
#define UPDT_H

#include "integrator.h"


#include "../bsdf/lambert.h"
#include "../bsdf/orennayar.h"


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

#endif // UPDT_H
