#ifndef BSDF_H
#define BSDF_H

#include <string>

#include "../sampling/sampler.h"

#include "../utility/embree_helper.h"
#include "../utility/math_helper.h"
#include "../utility/render_helper.h"
#include "../utility/usd_helper.h"


struct BSDF
{
    BSDF();

    virtual embree::Vec3f Evaluate(PixelSample& pixelSample,
        ShadingPoint& shadingPoint,
        BSDFSample& bsdfSample) = 0;
    virtual embree::Vec3fa Sample(PixelSample& pixelSample,
        ShadingPoint& shadingPoint,
        BSDFSample& bsdfSample) = 0;
    virtual float Pdf(PixelSample& pixelSample,
        ShadingPoint& shadingPoint,
        BSDFSample& bsdfSample) = 0;

    std::string _name;
};

#endif // BSDF_H
