#ifndef DISNEY_H
#define DISNEY_H

#include "material.h"

class Disney final : public Material
{
	public:
		Disney();

		virtual bool Evaluate() override;
		virtual bool Sample() override;
		virtual bool Pdf() override;
	private:
};

#endif // DISNEY_H
