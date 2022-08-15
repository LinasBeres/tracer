#ifndef CPU_GEOMETRY_H
#define CPU_GEOMETRY_H

#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>

#include <spindulys/math/vec3.h>
#include <spindulys/math/col3.h>

#include <geometry/geometry.h>

#include "../spindulysBackendCPU.h"


BACKEND_CPU_NAMESPACE_OPEN_SCOPE

class CPUGeometry : public Geometry
{
	public:
		CPUGeometry();
		virtual ~CPUGeometry();

		virtual bool Create(const RTCDevice& device, const RTCScene& topScene);
		virtual bool CreatePrototype(const RTCDevice& device);

		unsigned int GetGeomID() const { return _geomID; }
		unsigned int GetGeomInstanceID() const { return _geomInstanceID; }

	protected:
		unsigned int _geomID = RTC_INVALID_GEOMETRY_ID;
		unsigned int _geomInstanceID = RTC_INVALID_GEOMETRY_ID;

		RTCScene _scene = nullptr;
		RTCGeometry _geom = nullptr;
		RTCGeometry _geomInstance = nullptr;
	private:
};

BACKEND_CPU_NAMESPACE_CLOSE_SCOPE

#endif // CPU_GEOMETRY_H
