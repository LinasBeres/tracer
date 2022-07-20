#ifndef LAMBERT_H
#define LAMBERT_H

#include <string>

#include "../bsdf/bsdf.h"


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

#endif // LAMBERT_H
