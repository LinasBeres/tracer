#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <string>
#include <vector>
#include <mutex>
#include <unordered_map>

#include "../spindulysFrontend.h"

#include "../shapes/geometry.h"

#include "../utils/render_helper.h"
#include "../utils/usd_helper.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

struct SceneManager
{
    SceneManager();
    SceneManager(const std::string& scenePath);

    bool IsSceneValid(const std::string& scenePath);
    bool LoadScene(const std::string& scenePath);
    // bool LoadCamera();
    // bool LoadMaterials();
    bool LoadGeometry();
    bool LoadMeshGeometry();
    // bool LoadCurveGeometry();
    // bool LoadPrimitiveGeometry();

    pxr::UsdStageRefPtr _stage = nullptr;
    RTCDevice _device = nullptr;
    RTCScene _scene = nullptr; // Contains the instanced (single or not) geometry objects. This is the scene we are tracing against.
    // std::unordered_map<unsigned int, std::shared_ptr<Material>> _sceneMaterial;
    std::unordered_map<unsigned int, std::shared_ptr<Geometry>> _sceneGeom;
    std::mutex _sceneMutex;
};

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // SCENEMANAGER_H
