#ifndef EMPIRICAL_H
#define EMPIRICAL_H

#include "material.h"


class Empirical final : public Material
{
	public:
		Empirical();

		virtual bool Evaluate() override;
		virtual bool Sample() override;
		virtual bool Pdf() override;
	private:
};

#endif // EMPIRICAL_H
