#ifndef QUADMESH_H
#define QUADMESH_H

#include "spindulysFrontend.h"

#include "geometry.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

class QuadMesh : public Geometry
{
	public:
		QuadMesh();
		QuadMesh(const pxr::UsdPrim& prim,
				const pxr::UsdGeomMesh& usdGeom,
				const pxr::VtArray<pxr::GfVec3f>& points,
				const pxr::VtArray<int>& indices);

		virtual bool CreatePrototype(const RTCDevice& device) override;

	protected:
		pxr::VtArray<pxr::GfVec3f> _points;
		pxr::VtArray<int> _indices;
};

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // QUADMESH_H
