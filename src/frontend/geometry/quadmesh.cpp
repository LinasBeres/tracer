#include "quadmesh.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

QuadMesh::QuadMesh()
{
}

QuadMesh::QuadMesh(const pxr::UsdPrim& prim,
		const pxr::UsdGeomMesh& usdGeom,
		const pxr::VtArray<pxr::GfVec3f>& points,
		const pxr::VtArray<int>& indices)
{
	_prim = prim;
	_usdGeom = usdGeom;
	_points = points;
	_indices = indices;

	pxr::VtArray<pxr::GfVec3f> displayColor;
	_usdGeom.GetDisplayColorAttr().Get(&displayColor);

	_primName = _prim.GetName();
	// TODO: Get the display color from the correct time value.
	_displayColor = (displayColor.empty() ? Col3f(0.5f) :
			Col3f(displayColor[0][0],
						displayColor[0][1],
						displayColor[0][2]));
}

bool QuadMesh::CreatePrototype(const RTCDevice& device)
{
	_scene = rtcNewScene(device);
	_geom = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_QUAD);
	_geomID = rtcAttachGeometry(_scene, _geom);

	rtcSetSharedGeometryBuffer(_geom,
			RTC_BUFFER_TYPE_VERTEX,
			0,
			RTC_FORMAT_FLOAT3,
			_points.cdata(),
			0,
			sizeof(pxr::GfVec3f),
			_points.size());
	rtcSetSharedGeometryBuffer(_geom,
			RTC_BUFFER_TYPE_INDEX,
			0,
			RTC_FORMAT_UINT4,
			_indices.cdata(),
			0,
			sizeof(int) * 4,
			_indices.size() / 4);

	return true;
}


FRONTEND_NAMESPACE_CLOSE_SCOPE
