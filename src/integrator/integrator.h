#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "../material/material.h"
#include "../object/ray.h"
#include "../sampling/sampler.h"
#include "../scene/scenemanager.h"

#include "../utility/embree_helper.h"
#include <spindulysMath/helper.h>
#include "../utility/render_helper.h"


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
