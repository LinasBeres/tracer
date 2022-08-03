#ifndef POSITION_H
#define POSITION_H

#include "../spindulysFrontend.h"

#include "integrator.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

class PositionIntegrator final : public Integrator
{
	public:
		PositionIntegrator();

		virtual Col3f GetPixelColor(Ray& ray,
				PixelSample& pixelSample,
				SceneManager &sceneManager,
				const RenderGlobals& renderGlobals) override;
	private:
};

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // POSITION_H
