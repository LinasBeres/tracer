#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "../material/material.h"
#include "../object/ray.h"
#include "../sampling/sampler.h"
#include "../scene/scenemanager.h"

#include "../utility/embree_helper.h"
#include "../utility/math_helper.h"
#include "../utility/render_helper.h"


struct Integrator
{
    Integrator();

    virtual embree::Vec3f GetPixelColor(Ray& ray,
        PixelSample& pixelSample,
        SceneManager &sceneManager,
        const RenderGlobals& renderGlobals) = 0;
    virtual ShadingPoint SetupShadingPoint(SceneManager &sceneManager,
        const Ray& ray);

    std::string _handle;
};

#endif // INTEGRATOR_H
