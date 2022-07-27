#ifndef DISNEY_H
#define DISNEY_H

#include "../spindulysFrontend.h"

#include "material.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

class Disney final : public Material
{
	public:
		Disney();

		virtual bool Evaluate() override;
		virtual bool Sample() override;
		virtual bool Pdf() override;
	private:
};

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // DISNEY_H
