#ifndef LAMBERT_H
#define LAMBERT_H

#include <string>

#include "../bsdf/bsdf.h"

#include "../spindulysFrontend.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

class Lambert final : public BSDF
{
	public:
		Lambert();

		virtual embree::Vec3f Evaluate(PixelSample& pixelSample,
				ShadingPoint& shadingPoint,
				BSDFSample& bsdfSample) override;
		virtual embree::Vec3fa Sample(PixelSample& pixelSample,
				ShadingPoint& shadingPoint,
				BSDFSample& bsdfSample) override;
		virtual float Pdf(PixelSample& pixelSample,
				ShadingPoint& shadingPoint,
				BSDFSample& bsdfSample) override;
	private:
};

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // LAMBERT_H
