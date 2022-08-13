#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>
#include <mutex>
#include <unordered_map>

#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>

#include "../spindulysFrontend.h"

#include "../camera/camera.h"
#include "../shapes/geometry.h"

FRONTEND_NAMESPACE_OPEN_SCOPE

class Scene
{
	public:
		Scene() = default;
		Scene(const std::string& filepath);
		~Scene() = default;

		bool LoadScene(const std::string& filepath);
		bool LoadGeometry();
		bool LoadMeshGeometry();

		const std::string& GetFilePath() const { return filepath; }
		RTCScene GetScene() { return _scene; }

		const Geometry& GetGeometery(unsigned int geomInstanceID) const { return *(_sceneGeom.at(geomInstanceID).get()); }


	protected:
		std::string filepath;

		pxr::UsdStageRefPtr _stage = nullptr;
		RTCDevice _device = nullptr;
		RTCScene _scene = nullptr; // Contains the instanced (single or not) geometry objects. This is the scene we are tracing against.
															 // std::unordered_map<unsigned int, std::shared_ptr<Material>> _sceneMaterial;
		std::unordered_map<unsigned int, std::unique_ptr<Geometry>> _sceneGeom;

		std::mutex _sceneMutex;
	private:
};

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // SCENE_H
