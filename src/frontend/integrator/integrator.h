#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <spindulys/math/vec3.h>
#include <spindulys/math/col3.h>
#include <spindulys/mathHelper.h>

#include <spindulys/sampler.h>

#include "../spindulysFrontend.h"

#include "../shapes/ray.h"
#include "../scene/scenemanager.h"

#include "../utils/render_helper.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

class Integrator
{
	public:
		Integrator();

		virtual Col3f GetPixelColor(Ray& ray,
				PixelSample& pixelSample,
				SceneManager &sceneManager,
				const RenderGlobals& renderGlobals) = 0;
		virtual ShadingPoint SetupShadingPoint(SceneManager &sceneManager, const Ray& ray);

	protected:
		std::string _handle;
	private:
};

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // INTEGRATOR_H
