#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>

#include <spindulys/math/vec3.h>
#include <spindulys/math/col3.h>

#include "../spindulysFrontend.h"

#include "../utils/usd_helper.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

class Geometry
{
	public:
		Geometry();
		virtual ~Geometry();

		virtual bool Create(const RTCDevice& device,
				const RTCScene& topScene);
		virtual bool CreatePrototype(const RTCDevice& device);
		virtual bool CreateInstance(const RTCDevice& device,
				const RTCScene& topScene);
		virtual bool Commit();
		virtual bool CommitPrototype();
		virtual bool CommitInstance();
		virtual bool Update();
		virtual bool UpdatePrototype();
		virtual bool UpdateInstance();
		virtual bool Clean();

		const Col3f& GetDisplayColor() const { return _displayColor; }
		const pxr::GfMatrix4f GetTransform() const { return _transform; }
		unsigned int GetGeomInstanceID() const { return _geomInstanceID; }

	protected:
		unsigned int _geomID = RTC_INVALID_GEOMETRY_ID;
		unsigned int _geomInstanceID = RTC_INVALID_GEOMETRY_ID;

		RTCScene _scene = nullptr;
		RTCGeometry _geom = nullptr;
		RTCGeometry _geomInstance = nullptr;
		pxr::UsdPrim _prim;
		pxr::TfToken _primName;
		pxr::UsdGeomMesh _usdGeom;
		pxr::UsdGeomXformCache _usdGeomXformCache;
		pxr::GfMatrix4f _transform;
		Col3f _displayColor;
	private:
};

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // GEOMETRY_H
