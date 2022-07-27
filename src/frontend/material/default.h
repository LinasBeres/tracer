#ifndef DEFAULT_H
#define DEFAULT_H

#include "spindulysFrontend.h"

#include "material.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

struct Default : public Material
{
	public:
		Default();

		virtual bool Evaluate() override;
		virtual bool Sample() override;
		virtual bool Pdf() override;
	private:
};

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // DEFAULT_H
