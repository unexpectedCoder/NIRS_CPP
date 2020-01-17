#include "scene_types.h"

#include <fstream>
#include <math.h>
#include <QVector>


using namespace std;


Atmosphere::Atmosphere(const QString &path)
{
	// Init
	acc = nullptr;
	sLinearP = nullptr;
	sLinearRho = nullptr;
	sCubicT = nullptr;
	k = 1.4;

	// Try to open data file
	fstream file;
	if (path == "default")
		file.open("../../NIRS_CPP/scene/atmosphere.txt", ios_base::in);
	else
		file.open(path.toStdString(), ios_base::in);
	if (!file.is_open())
		throw "Error in <Atmosphere>: file is not found!";

	// Read data file
	QVector<double> height, temp, press, dens;

	int N = 0;
	while (true)
	{
		if (file.eof()) break;

		double h, t, p, rho;
		file >> h >> t >> p >> rho;
		p *= 1e5;
		height.push_back(h);
		temp.push_back(t);
		press.push_back(p);
		dens.push_back(rho);

		++N;
	}
	file.close();

	// Rewrite vector to array
	double *h = new double[N];
	double *t = new double[N];
	double *p = new double[N];
	double *rho = new double[N];
	for (int i = 0; i < N; ++i)
	{
		h[i] = height[i];
		t[i] = temp[i];
		p[i] = press[i];
		rho[i] = dens[i];
	}
	Hmin = height[0];
	Hmax = height[N - 1];

	// Init interpolation funcs
	acc = gsl_interp_accel_alloc();
	sLinearP = gsl_spline_alloc(gsl_interp_linear, N);
	sLinearRho = gsl_spline_alloc(gsl_interp_linear, N);
	sCubicT = gsl_spline_alloc(gsl_interp_cspline, N);

	gsl_spline_init(sLinearP, h, p, N);
	gsl_spline_init(sLinearRho, h, rho, N);
	gsl_spline_init(sCubicT, h, t, N);

	// Clear memory
	delete [] h;
	delete [] t;
	delete [] p;
	delete [] rho;
}


Atmosphere::~Atmosphere()
{
	if (sLinearP != nullptr) gsl_spline_free(sLinearP);
	if (sLinearRho != nullptr) gsl_spline_free(sLinearRho);
	if (sCubicT != nullptr) gsl_spline_free(sCubicT);
	if (acc != nullptr) gsl_interp_accel_free(acc);
}


double Atmosphere::T(double h) const {
	return gsl_spline_eval(sCubicT, h, acc);
}


double Atmosphere::p(double h) const {
	return gsl_spline_eval(sLinearP, h, acc);
}


double Atmosphere::rho(double h) const {
	return gsl_spline_eval(sLinearRho, h, acc);
}


double Atmosphere::sonic(double h) const {
	return sqrt(k * p(h) / rho(h));
}


ostream& operator <<(ostream &os, const Atmosphere &a)
{
	os << "Atmosphere GOST 4401-81:"
				"\n\t adiabatic index (k): " << a.k
		 << "\n\t height range: from " << a.Hmin * 1e-3 << " to " << a.Hmax * 1e-3 << " km\n";
	return os;
}
