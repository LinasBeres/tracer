#ifndef POSITION_H
#define POSITION_H

#include "integrator.h"


class PositionIntegrator final : public Integrator
{
	public:
		PositionIntegrator();

		virtual embree::Vec3f GetPixelColor(Ray& ray,
				PixelSample& pixelSample,
				SceneManager &sceneManager,
				const RenderGlobals& renderGlobals) override;
	private:
};

#endif // POSITION_H
