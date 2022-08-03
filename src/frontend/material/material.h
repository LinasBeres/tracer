#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

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
