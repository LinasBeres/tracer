#ifndef EMPIRICAL_H
#define EMPIRICAL_H

#include "../spindulysFrontend.h"

#include "material.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

class Empirical final : public Material
{
	public:
		Empirical();

		virtual bool Evaluate() override;
		virtual bool Sample() override;
		virtual bool Pdf() override;
	private:
};

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // EMPIRICAL_H
