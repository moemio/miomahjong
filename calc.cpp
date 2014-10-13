#include "defs.h"
#include "calc.h"

double f1(double a, double b, double c, double x)
{
	return a*exp(-((x-b)*(x-b)/(c*c)));
}


