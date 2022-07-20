#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

#include "../utility/embree_helper.h"


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

#endif // MATERIAL_H
