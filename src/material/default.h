#ifndef DEFAULT_H
#define DEFAULT_H

#include "material.h"


struct Default : public Material
{
	public:
		Default();

		virtual bool Evaluate() override;
		virtual bool Sample() override;
		virtual bool Pdf() override;
	private:
};

#endif // DEFAULT_H
