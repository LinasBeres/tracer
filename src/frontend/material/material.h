#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

#include <embree3/common/math/vec2.h>
#include <embree3/common/math/vec3.h>
#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>

#include "../spindulysFrontend.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

class Material
{
	public:
		Material() = default;

		virtual bool Evaluate() = 0;
		virtual bool Sample() = 0;
		virtual bool Pdf() = 0;

	protected:
		std::string _name;
};

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // MATERIAL_H
