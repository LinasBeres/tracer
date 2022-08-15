#include "quadmesh.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

QuadMesh::QuadMesh()
{
}

QuadMesh::QuadMesh(const pxr::TfToken& primName,
		const pxr::GfMatrix4f& transform,
		const Col3f& displayColor,
		const pxr::VtArray<pxr::GfVec3f>& points,
		const pxr::VtArray<int>& indices)
{
	_points = points;
	_indices = indices;

	_primName = primName;

	_transform = transform;

	_displayColor = displayColor;
}


FRONTEND_NAMESPACE_CLOSE_SCOPE
