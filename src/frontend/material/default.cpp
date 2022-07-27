#include "default.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

Default::Default()
{
	_name = "defualt";
}

bool Default::Evaluate()
{
	return true;
}

bool Default::Sample()
{
	return true;
}

bool Default::Pdf()
{
	return true;
}

FRONTEND_NAMESPACE_CLOSE_SCOPE
