#ifndef BUFFER_H
#define BUFFER_H

#include <vector>

#include <embree3/common/math/vec2.h>
#include <embree3/common/math/vec3.h>
#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>

#include "../spindulysFrontend.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

class Buffer
{
	public:
		Buffer() = default;

		void Init(int width, int height);
		void Clean(int width, int height);
		void Swap(Buffer& buffer);

		void SwapPixelData(const std::vector<embree::Vec3f>& pixelData) { _pixelData = pixelData; }
		const std::vector<embree::Vec3f>& GetPixelData() const { return _pixelData; }

		void SetPixel(int pixelIndex, const embree::Vec3f& pixel) { _pixelData[pixelIndex] = pixel; }
		const embree::Vec3f& GetPixel(int pixelIndex) const { return _pixelData[pixelIndex]; }


	private:
		std::vector<embree::Vec3f> _pixelData;
};

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // BUFFER_H
