#ifndef BSDF_H
#define BSDF_H

#include <string>

#include <spindulysMath/helper.h>

#include <embree3/common/math/vec2.h>
#include <embree3/common/math/vec3.h>
#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>

#include "../sampling/sampler.h"

#include "../utils/render_helper.h"
#include "../utils/usd_helper.h"


class BSDF
{
	public:
		BSDF() = default;

		virtual embree::Vec3f Evaluate(PixelSample& pixelSample,
				ShadingPoint& shadingPoint,
				BSDFSample& bsdfSample) = 0;
		virtual embree::Vec3fa Sample(PixelSample& pixelSample,
				ShadingPoint& shadingPoint,
				BSDFSample& bsdfSample) = 0;
		virtual float Pdf(PixelSample& pixelSample,
				ShadingPoint& shadingPoint,
				BSDFSample& bsdfSample) = 0;

	protected:
		std::string _name;
	private:
};

#endif // BSDF_H
