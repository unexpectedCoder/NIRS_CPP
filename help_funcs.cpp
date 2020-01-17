#include "help_funcs.h"

#include <math.h>


double Funcs::deg2rad(double deg) {
	return M_PI * deg / 180.0;
}


double Funcs::rad2deg(double rad) {
	return 180.0 * rad / M_PI;
}
