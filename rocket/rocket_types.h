#ifndef ROCKET_TYPES_H
#define ROCKET_TYPES_H

#include <iostream>
#include <QString>


struct Coordinates;
struct StartConds;
struct Parameters;
struct Constraints;
struct Compartment;
struct Compartment;
struct Engine;
struct State;


struct Coordinates
{
	// N-D coordinates type
	int outAcc;			// Accuracy of the output
	int dim;				// Dimension
	double *x;			// Coordinates data

	Coordinates();
	Coordinates(int dim);
	Coordinates(double *coords, int dim);
	Coordinates(const Coordinates &cs);
	Coordinates(const Coordinates *cs);
	~Coordinates();

	void update(const Coordinates *cs);

	friend std::ostream& operator <<(std::ostream &os, const Coordinates &cs);
};


struct StartConds
{
	// Starting conditions type
	Coordinates *coords;	// Starting coordinates
	double V, mu, Theta;	// Starting velocity,
												// relative fuel supply,
												// angle of inclination to the horizon

	StartConds();
	StartConds(int dim);
	StartConds(const Coordinates &cs, double V, double mu, double Theta_deg);
	~StartConds();

	const Coordinates* getCoords() const;

	friend std::ostream& operator <<(std::ostream &os, const StartConds &sc);
};


struct Parameters
{
	// Common rocket's parameters type
	double
	icx,			// Coefficient of the rocket form
	q_m,			// Middle load
	lambdaL,	// Lengthening of corpus
	beta;			// Coefficient of the construction excellence

	Parameters(double icx, double q_m, double lengthening, double beta) :
		icx(icx), q_m(q_m), lambdaL(lengthening), beta(beta) {}

	friend std::ostream& operator <<(std::ostream &os, const Parameters &p);
};


struct Constraints
{
	// Simulation constraints type
	double
	muMax,		// Max relative propellant mass
	Dmax,			// Max flying distance
	Hmax,		// Max flight height
	nyMax;		// Max transverse overload

	Constraints() : muMax(0.0), Dmax(0.0), Hmax(0.0), nyMax(0.0) {}
	Constraints(double maxD_km, double maxH_km, double maxMu, double maxNy);

	Constraints& operator =(const Constraints &cs);
	friend std::ostream& operator <<(std::ostream &os, const Constraints &c);
};


struct Compartment
{
	// Rocket's part type
	QString name;
	int index;
	double mass;

	Compartment() : name("--NONAME--"), index(-1), mass(0.0) {}
	Compartment(const QString &name, int indx, double m);

	friend std::ostream& operator <<(std::ostream &os, const Compartment &c);
};


struct Engine
{
	// Rocket's engine type
	int mode;					// Current working mode
	int modes;				// Amount of engine working modes
	double *eta;			// Thrust-to-weight ratio
	double *I_1;			// Single impulse
	double *p0;				// Pressure in the combustion chamber
	double *p_outlet;	// Nozzle outlet pressure
	double *k;				// Adiabatic index of combustion products

	Engine() : mode(0), modes(0),
		eta(nullptr), I_1(nullptr), p0(nullptr), p_outlet(nullptr), k(nullptr) {}
	Engine(int modes, double *eta, double *I_1,
				 double *p0_MPa, double *p_outlet_MPa, double *k);
	Engine(const Engine &en);
	Engine(const Engine *en);
	~Engine();

	friend std::ostream& operator <<(std::ostream &os, const Engine &en);
};


struct State
{
	// Current rocket's state type
	Coordinates *coords;
	double
	V,
	mu,
	Theta;

	State() : coords(nullptr), V(0.0), mu(0.0), Theta(0.0) {}
	State(const StartConds *sc);
	~State() {
		if (coords != nullptr) delete coords;
	}

	void update(const Coordinates *cs, double velo, double mu, double Theta);

	friend std::ostream& operator <<(std::ostream &os, const State &s);
};

#endif // ROCKET_TYPES_H
