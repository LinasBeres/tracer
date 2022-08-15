#include "scene.h"

#include <tbb/blocked_range2d.h>
#include <tbb/blocked_range3d.h>
#include <tbb/parallel_for.h>
#include <tbb/parallel_for_each.h>

#include "../shapes/trianglemesh.h"
#include "../shapes/quadmesh.h"

FRONTEND_NAMESPACE_OPEN_SCOPE

Scene::Scene(const std::string& filepath)
	: filepath(filepath)
{
	LoadScene(filepath);
}

bool Scene::LoadScene(const std::string& filepath)
{
	if (!((std::size_t(filepath.rfind(std::string(".usd")) != std::string::npos) ||
        std::size_t(filepath.rfind(std::string(".usda")) != std::string::npos) ||
        std::size_t(filepath.rfind(std::string(".usdc")) != std::string::npos) ||
        std::size_t(filepath.rfind(std::string(".usdz")) != std::string::npos)) ? true : false))
	{
		std::cerr << "ERROR - The following file is not an USD scene: " << filepath << std::endl;

		return false;
	}

	_stage = pxr::UsdStage::Open(filepath);

	if (!_stage)
		return false;

	_device = rtcNewDevice("");
	_scene = rtcNewScene(_device);

	LoadGeometry();

	rtcCommitScene(_scene);

	return true;
}

bool Scene::LoadGeometry()
{
	LoadMeshGeometry();

	return true;
}

bool Scene::LoadMeshGeometry()
{
	std::vector<pxr::UsdPrim> meshPrims;

	GetPrimFromType("Mesh", _stage, pxr::SdfPath("/"), meshPrims);

	tbb::parallel_for_each(meshPrims.begin(), meshPrims.end(), [&](pxr::UsdPrim& prim)
			{
			const pxr::TfToken primName(prim.GetName());
			const pxr::SdfPath primPath(prim.GetPrimPath());

			pxr::UsdGeomMesh usdGeom(pxr::UsdGeomMesh::Get(_stage, primPath));

			pxr::VtArray<pxr::GfVec3f> points;
			pxr::VtArray<int> indicesCounts;
			pxr::VtArray<int> indices;

			usdGeom.GetPointsAttr().Get(&points);
			usdGeom.GetFaceVertexIndicesAttr().Get(&indices);
			usdGeom.GetFaceVertexCountsAttr().Get(&indicesCounts);

			bool isTriangleMesh((static_cast<float>(indices.size()) /
						static_cast<float>(indicesCounts.size()) == 3.0f) ? true : false);
			bool isQuadMesh((static_cast<float>(indices.size()) /
						static_cast<float>(indicesCounts.size()) == 4.0f) ? true : false);
			bool needTriangulate((!isTriangleMesh && !isQuadMesh) ? true : false);

			if (isTriangleMesh)
			{
				TriangleMesh triangleMesh(prim, usdGeom, points, indices);
				triangleMesh.Create(_device, _scene);

				_sceneMutex.lock();
				_sceneGeom[triangleMesh.GetGeomInstanceID()] = triangleMesh;
				_sceneMutex.unlock();
			}
			else if (isQuadMesh)
			{
				QuadMesh quadMesh(prim, usdGeom, points, indices);
				quadMesh.Create(_device, _scene);

				_sceneMutex.lock();
				_sceneGeom[quadMesh.GetGeomInstanceID()] = quadMesh;
				_sceneMutex.unlock();
			}
			else if (needTriangulate)
			{
				// TODO
			}
			else
			{
				// TODO
			}
			});

	return true;
}

FRONTEND_NAMESPACE_CLOSE_SCOPE

