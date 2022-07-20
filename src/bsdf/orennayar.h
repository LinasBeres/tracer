#ifndef ORENNAYAR_H
#define ORENNAYAR_H

#include <string>

#include "bsdf.h"


class OrenNayar final : public BSDF
{
	public:
		OrenNayar();

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
		float _roughness;
};

#endif // ORENNAYAR_H
