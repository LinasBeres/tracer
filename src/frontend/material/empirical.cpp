#include "empirical.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

Empirical::Empirical()
{
	_name = "empirical";
}

bool Empirical::Evaluate()
{
	return true;
}

bool Empirical::Sample()
{
	return true;
}

bool Empirical::Pdf()
{
	return true;
}

FRONTEND_NAMESPACE_CLOSE_SCOPE
