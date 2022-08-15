#include "cpuQuadmesh.h"


BACKEND_CPU_NAMESPACE_OPEN_SCOPE

CPUQuadMesh::CPUQuadMesh(const std::string& primName,
		const LinearSpace3f& transform,
		const Col3f& displayColor,
		const pxr::VtArray<pxr::GfVec3f>& points,
		const pxr::VtArray<int>& indices)
	: QuadMesh(primName, transform, displayColor, points, indices)
{
}

bool CPUQuadMesh::CreatePrototype(const RTCDevice& device)
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


BACKEND_CPU_NAMESPACE_CLOSE_SCOPE
