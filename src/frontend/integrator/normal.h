#ifndef NORMAL_H
#define NORMAL_H

#include "integrator.h"


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

#endif // NORMAL_H
