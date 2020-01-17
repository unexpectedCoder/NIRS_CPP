#ifndef SCENE_TYPES_H
#define SCENE_TYPES_H

#include <iostream>
#include <QString>

#include "gsl/gsl_spline.h"


struct Atmosphere
{
public:
	Atmosphere(const QString &path = "default");
	~Atmosphere();

	double T(double h) const;
	double p(double h) const;
	double rho(double h) const;
	double sonic(double h) const;

	friend std::ostream& operator <<(std::ostream &os, const Atmosphere &a);

public:
	double k;
	double Hmin, Hmax;

private:
	gsl_interp_accel *acc;
	gsl_spline
	*sLinearRho,
	*sLinearP,
	*sCubicT;
};

#endif // SCENE_TYPES_H
