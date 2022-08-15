#include "cpuScene.h"


BACKEND_CPU_NAMESPACE_OPEN_SCOPE

CPUScene::CPUScene()
{
	_device = rtcNewDevice("");
	_scene = rtcNewScene(_device);
}

bool CPUScene::CommitGeometry()
{

	std::cerr << "COMMIT GEOM FROM CPU GOOOOODDDD\n";

	for (const auto& it : _sceneGeom)
	{
		Geometry geom = it.second;

		geom.Create(_device, _scene);
	}

	rtcCommitScene(_scene);

	return true;
}

BACKEND_CPU_NAMESPACE_CLOSE_SCOPE
