#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include "geometry.h"


class TriangleMesh final : public Geometry
{
	public:
		TriangleMesh();
		TriangleMesh(const pxr::UsdPrim& prim,
				const pxr::UsdGeomMesh& usdGeom,
				const pxr::VtArray<pxr::GfVec3f>& points,
				const pxr::VtArray<int>& indices);

		virtual bool CreatePrototype(const RTCDevice& device) override;
		virtual bool UpdatePrototype() override;

	private:
		pxr::VtArray<pxr::GfVec3f> _points;
		pxr::VtArray<int> _indices;
};

#endif // TRIANGLEMESH_H
