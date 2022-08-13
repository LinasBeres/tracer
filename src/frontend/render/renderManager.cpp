#include "renderManager.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

RenderManager::RenderManager(const std::string& filepath)
{
	scene.LoadScene(filepath);
}

FRONTEND_NAMESPACE_CLOSE_SCOPE
