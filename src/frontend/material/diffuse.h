#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "../spindulysFrontend.h"

#include "material.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

class Diffuse final : public Material
{
	public:
		Diffuse();

		virtual bool Evaluate() override;
		virtual bool Sample() override;
		virtual bool Pdf() override;
	private:
};

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // DIFFUSE_H
