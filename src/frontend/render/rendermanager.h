#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <memory>
#include <vector>

#include <config.h>

#include <camera/camera.h>

#include "../shapes/buffer.h"
#include "../integrator/integrator.h"
#include "../shapes/ray.h"
#include "../scene/scenemanager.h"
#include "../sampling/sampler.h"

#include "../utils/render_helper.h"
#include "../utils/tbb_helper.h"

#include "../integrator/udpt.h"
#include "../integrator/diffuse.h"
#include "../integrator/occlusion.h"
#include "../integrator/position.h"
#include "../integrator/normal.h"
#include "../integrator/debug.h"

SPINDULYS_NAMESPACE_OPEN_SCOPE

class RenderManager
{
	public:
		RenderManager();

		void Trace(const RenderGlobals& renderGlobals,
				SceneManager& sceneManager,
				Camera& camera,
				Buffer& buffer,
				int iterations);

		IntegratorIds integratorID = IntegratorIds::UDPT;

	private:
		std::vector<std::shared_ptr<Integrator>> integrators {
			std::make_shared<UDPTIntegrator>(),
				std::make_shared<DiffuseIntegrator>(),
				std::make_shared<OcclusionIntegrator>(),
				std::make_shared<PositionIntegrator>(),
				std::make_shared<NormalIntegrator>(),
				std::make_shared<DebugIntegrator>()
		};
};

SPINDULYS_NAMESPACE_CLOSE_SCOPE

#endif // RENDERMANAGER_H
