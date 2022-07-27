#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <embree3/common/math/vec2.h>
#include <embree3/common/math/vec3.h>
#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>

#include <spindulys/mathHelper.h>

#include "../spindulysFrontend.h"

#include "../material/material.h"
#include "../shapes/ray.h"
#include "../sampling/sampler.h"
#include "../scene/scenemanager.h"

#include "../utils/render_helper.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

class Integrator
{
	public:
		Integrator();

		virtual embree::Vec3f GetPixelColor(Ray& ray,
				PixelSample& pixelSample,
				SceneManager &sceneManager,
				const RenderGlobals& renderGlobals) = 0;
		virtual ShadingPoint SetupShadingPoint(SceneManager &sceneManager,
				const Ray& ray);

	protected:
		std::string _handle;
	private:
};

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // INTEGRATOR_H
