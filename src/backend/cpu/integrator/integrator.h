#ifndef CPU_INTGRATOR_H
#define CPU_INTGRATOR_H

#include <spindulys/math/col3.h>

#include <scene/scenemanager.h>

#include "../spindulysBackendCPU.h"

#include "../utils/ray.h"

BACKEND_CPU_NAMESPACE_OPEN_SCOPE

class Integrator
{
	public:
		Integrator();

		virtual Col3f GetPixelColor(Ray& ray,
				PixelSample& pixelSample,
				SceneManager &scene,
				const RenderGlobals& renderGlobals) = 0;
		virtual ShadingPoint SetupShadingPoint(SceneManager &scene, const Ray& ray);

	private:
};

BACKEND_CPU_NAMESPACE_CLOSE_SCOPE

#endif // CPU_INTGRATOR_H
