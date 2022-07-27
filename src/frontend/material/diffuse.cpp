#include "diffuse.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

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

FRONTEND_NAMESPACE_CLOSE_SCOPE
