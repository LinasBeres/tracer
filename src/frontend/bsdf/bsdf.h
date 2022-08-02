#ifndef BSDF_H
#define BSDF_H

#include <string>

#include <spindulys/mathHelper.h>

#include <spindulys/math/vec3.h>

#include "../spindulysFrontend.h"

#include "../sampling/sampler.h"

#include "../utils/render_helper.h"
#include "../utils/usd_helper.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

class BSDF
{
	public:
		BSDF() = default;

		virtual Vec3f Evaluate(PixelSample& pixelSample,
				ShadingPoint& shadingPoint,
				BSDFSample& bsdfSample) = 0;
		virtual Vec3f Sample(PixelSample& pixelSample,
				ShadingPoint& shadingPoint,
				BSDFSample& bsdfSample) = 0;
		virtual float Pdf(PixelSample& pixelSample,
				ShadingPoint& shadingPoint,
				BSDFSample& bsdfSample) = 0;

	protected:
		std::string _name;
	private:
};

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // BSDF_H
