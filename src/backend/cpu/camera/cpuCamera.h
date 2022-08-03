#ifndef CPU_CAMERA_H
#define CPU_CAMERA_H

#include "../spindulysBackendCPU.h"

#include <camera/camera.h>

#include "../utils/ray.h"


BACKEND_CPU_NAMESPACE_OPEN_SCOPE

class CPUCamera final : Camera
{
	public:
		CPUCamera() = default;
		~CPUCamera() = default;

	Ray GetCameraRay(const PixelSample& pixelSample);
};

BACKEND_CPU_NAMESPACE_CLOSE_SCOPE

#endif //CPU_CAMERA_H
