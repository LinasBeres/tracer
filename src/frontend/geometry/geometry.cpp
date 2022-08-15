#include "geometry.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

Geometry::Geometry()
{
}

Geometry::~Geometry()
{

}

bool Geometry::Create(const RTCDevice& device,
		const RTCScene& topScene)
{
	CreatePrototype(device);

	rtcCommitGeometry(_geom);
	rtcReleaseGeometry(_geom);

	rtcCommitScene(_scene);

	_geomInstance = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_INSTANCE);
	_geomInstanceID = rtcAttachGeometry(topScene, _geomInstance);

	rtcSetGeometryInstancedScene(_geomInstance, _scene);
	rtcSetGeometryTimeStepCount(_geomInstance, 1);

	pxr::GfMatrix4d usdTransform(_usdGeomXformCache.GetLocalToWorldTransform(_prim));
	_transform = pxr::GfMatrix4f(usdTransform);

	rtcSetGeometryTransform(_geomInstance,
			0,
			RTC_FORMAT_FLOAT4X4_COLUMN_MAJOR,
			_transform.GetArray());

	rtcCommitGeometry(_geomInstance);
	rtcReleaseGeometry(_geomInstance);

	return true;
}

bool Geometry::CreatePrototype(const RTCDevice& device)
{
	return true;
}



FRONTEND_NAMESPACE_CLOSE_SCOPE
