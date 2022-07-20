#include "diffuse.h"


Diffuse::Diffuse()
{
	_name = "diffuse";
}

bool Diffuse::Evaluate()
{
	return true;
}

bool Diffuse::Sample()
{
	return true;
}

bool Diffuse::Pdf()
{
	return true;
}
