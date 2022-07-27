#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <embree3/common/math/vec2.h>
#include <embree3/common/math/vec3.h>
#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>

#include <spindulysMath/helper.h>

#include "../material/material.h"
#include "../shapes/ray.h"
#include "../sampling/sampler.h"
#include "../scene/scenemanager.h"

#include "../utils/render_helper.h"


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

#endif // INTEGRATOR_H
