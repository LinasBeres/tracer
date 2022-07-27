#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "material.h"

class Diffuse final : public Material
{
	public:
		Diffuse();

		virtual bool Evaluate() override;
		virtual bool Sample() override;
		virtual bool Pdf() override;
	private:
};

#endif // DIFFUSE_H
