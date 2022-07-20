#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "../utility/embree_helper.h"
#include "../utility/usd_helper.h"


class Geometry
{
	public:
		Geometry();

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

		const embree::Vec3f& GetDisplayColor() const { return _displayColor; }
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
		embree::Vec3f _displayColor;
	private:
};

#endif // GEOMETRY_H
