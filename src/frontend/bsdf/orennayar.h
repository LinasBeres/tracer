#ifndef ORENNAYAR_H
#define ORENNAYAR_H

#include <string>

#include "../spindulysFrontend.h"

#include "bsdf.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

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

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // ORENNAYAR_H
