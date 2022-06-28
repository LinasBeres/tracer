#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <memory>
#include <vector>

#include <glad/glad.h>

#include "../object/buffer.h"
#include "../camera/camera.h"
#include "../opengl/glshader.h"
#include "../integrator/integrator.h"
#include "../object/ray.h"
#include "../scene/scenemanager.h"
#include "../sampling/sampler.h"

#include "../utility/render_helper.h"
#include "../utility/tbb_helper.h"

#include "../integrator/udpt.h"
#include "../integrator/diffuse.h"
#include "../integrator/occlusion.h"
#include "../integrator/position.h"
#include "../integrator/normal.h"
#include "../integrator/debug.h"


struct RenderManager
{
    RenderManager();

    void Trace(const RenderGlobals& renderGlobals,
        SceneManager& sceneManager,
        Camera& camera,
        Buffer& buffer,
        int iterations);
    void RenderToScreenTexture(int width,
        int height,
        Buffer& buffer);
    void SetupScreenQuad(int width,
        int height);
    void CleanScreenQuad();
    void DrawScreenQuad();

    unsigned int integratorID = UDPT;

    private:
        GLuint screenQuadVAO;
        GLuint screenQuadVBO;
        GLuint screenTextureID;

        GLShader screenQuadShader;
        std::vector<std::shared_ptr<Integrator>> integrators {
            std::make_shared<UDPTIntegrator>(),
            std::make_shared<DiffuseIntegrator>(),
            std::make_shared<OcclusionIntegrator>(),
            std::make_shared<PositionIntegrator>(),
            std::make_shared<NormalIntegrator>(),
            std::make_shared<DebugIntegrator>()
        };
};

#endif // RENDERMANAGER_H
