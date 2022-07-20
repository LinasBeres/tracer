#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "integrator.h"


class DiffuseIntegrator final : public Integrator
{
	public:
		DiffuseIntegrator();

		virtual embree::Vec3f GetPixelColor(Ray& ray,
				PixelSample& pixelSample,
				SceneManager &sceneManager,
				const RenderGlobals& renderGlobals) override;
	private:
};

#endif // DIFFUSE_H
