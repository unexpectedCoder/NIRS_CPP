#include "rocket_types.h"
#include "help_funcs.h"

#include <iomanip>


using namespace std;


// Coordinates
Coordinates::Coordinates()
{
	x = nullptr;
	dim = 0;
	outAcc = 3;
}


Coordinates::Coordinates(int dim)
{
	if (dim < 1)
		throw "Error in <Coordinates>: dimension must be > 0!";

	this->dim = dim;
	x = new double[this->dim];
	for (int i = 0; i < this->dim; ++i)
		x[i] = 0.0;
	outAcc = 3;
}


Coordinates::Coordinates(double *coords, int dim)
{
	if (dim < 1)
		throw "Error in <Coordinates>: dimension must be > 0!";

	this->dim = dim;
	x = new double[this->dim];
	for (int i = 0; i < this->dim; ++i)
		x[i] = coords[i];
	outAcc = 3;
}


Coordinates::Coordinates(const Coordinates &cs)
{
	dim = cs.dim;
	if (dim > 0)
		for (int i = 0; i < dim; ++i)
			x[i] = cs.x[i];
	else
		x = nullptr;
	outAcc = cs.outAcc;
}


Coordinates::Coordinates(const Coordinates *cs)
{
	dim = cs->dim;
	if (dim > 0)
		for (int i = 0; i < dim; ++i)
			x[i] = cs->x[i];
	else
		x = nullptr;
	outAcc = cs->outAcc;
}


Coordinates::~Coordinates()
{
	if (x != nullptr && dim != 0) delete [] x;
}


void Coordinates::update(const Coordinates *cs)
{
	dim = cs->dim;
	if (dim > 0)
		for (int i = 0; i < dim; ++i)
			x[i] = cs->x[i];
	else
		x = nullptr;
	outAcc = cs->outAcc;
}


ostream& operator <<(ostream &os, const Coordinates &cs)
{
	if (cs.x != nullptr)
	{
		os << "Coordinates " << cs.dim << "D: (" << setprecision(cs.outAcc) << cs.x[0];
		for (int i = 1; i < cs.dim; ++i)
		{
			if (cs.outAcc < 0)
				os << "; " << setprecision(0) << cs.x[i];
			else
				os << "; " << setprecision(cs.outAcc) << cs.x[i];
		}
		os << ")\n";
	}
	else
		os << "Coordinates is empty...\n";
	return os;
}


// Starting conditions
StartConds::StartConds()
{
	coords = nullptr;
	V = 0.0;
	mu = 0.0;
	Theta = 0.0;
}


StartConds::StartConds(int dim)
{
	if (dim < 1)
		throw "Error in <StartConds>: dimension must be > 0!";

	coords = new Coordinates(dim);
	V = 0.0;
	mu = 0.0;
	Theta = 0.0;
}


StartConds::StartConds(const Coordinates &cs, double V, double mu, double Theta_deg)
{
	coords = new Coordinates(cs);
	this->V = V;
	this->mu = mu;
	Theta = Funcs::deg2rad(Theta_deg);
}


StartConds::~StartConds()
{
	if (coords != nullptr) delete coords;
}


const Coordinates* StartConds::getCoords() const {
	return coords;
}


ostream& operator <<(ostream &os, const StartConds &sc)
{
	os << "Starting conditions:"
		 << "\t " << *sc.coords
		 << "\t velocity (V), m/s: " << sc.V
		 << "\t relative fuel supply (mu): " << sc.mu
		 << "\t angle of inclination to the horizon (Theta), deg: " << Funcs::rad2deg(sc.Theta) << '\n';
	return os;
}


// Compartment
Compartment::Compartment(const QString &n, int indx, double m)
{
	if (m < 0.0)
		throw "Error in <Compartment>: mass cannot be a negative!";
	if (indx < 0)
		throw "Error in <Compartment>: index must be possitive!";
	name = n;
	index = indx;
	mass = m;
}


ostream& operator <<(ostream &os, const Compartment &c)
{
	os << "Compartment #" << c.index << " \"" << c.name.toStdString() << '"'
		 << "\n\t mass, kg: " << c.mass << '\n';
	return os;
}


// Engine
Engine::Engine(int modes, double *eta, double *I_1,
							 double *p0_MPa, double *p_outlet_MPa, double *k)
{
	if (modes < 1)
		throw "Error in <Engine>: amount of engine working modes cannot be < 1!";

	mode = 0;
	this->modes = modes;
	this->eta = new double[this->modes];
	this->I_1 = new double[this->modes];
	this->p0 = new double[this->modes];
	this->p_outlet = new double[this->modes];
	this->k = new double[this->modes];

	for (int i = 0; i < this->modes; ++i)
	{
		this->eta[i] = eta[i];
		this->I_1[i] = I_1[i];
		this->p0[i] = p0_MPa[i] * 1e6;
		this->p_outlet[i] = p_outlet_MPa[i] * 1e6;
		this->k[i] = k[i];
	}
}


Engine::Engine(const Engine &en)
{
	mode = en.mode;
	modes = en.modes;
	if (en.eta != nullptr)
	{
		eta = new double[modes];
		for (int i = 0; i < modes; ++i)
			eta[i] = en.eta[i];
	}
	if (en.I_1 != nullptr)
	{
		I_1 = new double[modes];
		for (int i = 0; i < modes; ++i)
			I_1[i] = en.I_1[i];
	}
	if (en.p0 != nullptr)
	{
		p0 = new double[modes];
		for (int i = 0; i < modes; ++i)
			p0[i] = en.p0[i];
	}
	if (en.p_outlet != nullptr)
	{
		p_outlet = new double[modes];
		for (int i = 0; i < modes; ++i)
			p_outlet[i] = en.p_outlet[i];
	}
	if (en.k != nullptr)
	{
		k = new double[modes];
		for (int i = 0; i < modes; ++i)
			k[i] = en.k[i];
	}
}


Engine::Engine(const Engine *en)
{
	mode = en->mode;
	modes = en->modes;
	if (en->eta != nullptr)
	{
		eta = new double[modes];
		for (int i = 0; i < modes; ++i)
			eta[i] = en->eta[i];
	}
	if (en->I_1 != nullptr)
	{
		I_1 = new double[modes];
		for (int i = 0; i < modes; ++i)
			I_1[i] = en->I_1[i];
	}
	if (en->p0 != nullptr)
	{
		p0 = new double[modes];
		for (int i = 0; i < modes; ++i)
			p0[i] = en->p0[i];
	}
	if (en->p_outlet != nullptr)
	{
		p_outlet = new double[modes];
		for (int i = 0; i < modes; ++i)
			p_outlet[i] = en->p_outlet[i];
	}
	if (en->k != nullptr)
	{
		k = new double[modes];
		for (int i = 0; i < modes; ++i)
			k[i] = en->k[i];
	}
}


Engine::~Engine()
{
	if (eta != nullptr) delete [] eta;
	if (I_1 != nullptr) delete [] I_1;
	if (p0 != nullptr) delete [] p0;
	if (p_outlet != nullptr) delete [] p_outlet;
	if (k != nullptr) delete [] k;
}


ostream& operator <<(ostream &os, const Engine &en)
{
	os << "Engine:"
				"\n\t amount of working modes: " << en.modes
		 << "\n\t thrust-to-weight ratio (eta): [";
	for (int i = 0; i < en.modes - 1; ++i)
		os << en.eta[i] << "; ";
	os << en.eta[en.modes - 1] << ']';

	os << "\n\t single impulse (I_1), m/s: [";
	for (int i = 0; i < en.modes - 1; ++i)
		os << en.I_1[i] << "; ";
	os << en.I_1[en.modes - 1] << ']';

	os << "\n\t CC pressure (p0), MPa: [";
	for (int i = 0; i < en.modes - 1; ++i)
		os << en.p0[i] * 1e-6 << "; ";
	os << en.p0[en.modes - 1] * 1e-6 << ']';

	os << "\n\t Nozzle outlet pressure (p_outlet), MPa: [";
	for (int i = 0; i < en.modes - 1; ++i)
		os << en.p_outlet[i] * 1e-6 << "; ";
	os << en.p_outlet[en.modes - 1] * 1e-6 << ']';

	os << "\n\t adiabatic index of gases (k): [";
	for (int i = 0; i < en.modes - 1; ++i)
		os << en.k[i] << "; ";
	os << en.k[en.modes - 1] << "]\n";

	return os;
}


// Parameters
ostream& operator <<(ostream &os, const Parameters &p)
{
	os << "Parameters:"
				"\n\t coefficient of the rocket form (icx): " << p.icx
		 << "\n\t middle load (q_m), Pa: " << p.q_m
		 << "\n\t lengthening of corpus (lambdaL): " << p.lambdaL
		 << "\n\t coefficient of the construction excellence (beta): " << p.beta << '\n';
	return os;
}


// Constraints
Constraints::Constraints(double maxD_km, double maxH_km, double maxMu, double maxNy)
{
	if (maxD_km < 0.0)
		throw "Error in <Constraints>: distance cannot be negative!";
	if (maxH_km < 0.0)
		throw "Error in <Constraints>: height cannot be negative!";
	if (maxMu < 0.0 || maxMu > 1.0)
		throw "Error in <Constraints>: relative fuel mass must be in range (0; 1]!";
	if (maxNy < 1.0)
		throw "Error in <Constraints>: overload must be >= 1!";

	Dmax = maxD_km * 1e3;
	Hmax = maxH_km * 1e3;
	muMax = maxMu;
	nyMax = maxNy;
}


Constraints &Constraints::operator =(const Constraints &cs)
{
	if (this == &cs)
		return *this;
	Dmax = cs.Dmax;
	Hmax = cs.Dmax;
	muMax = cs.muMax;
	nyMax = cs.nyMax;
	return *this;
}


ostream& operator <<(ostream &os, const Constraints &c)
{
	os << "Constraints:"
				"\n\t max distance (Dmax), km: " << c.Dmax * 1e-3
		 << "\n\t max height (Hmax), km: " << c.Hmax * 1e-3
		 << "\n\t max relative fuel mass (muMax): " << c.muMax
		 << "\n\t max transverse overload (nyMax): " << c.nyMax << '\n';
	return os;
}


// State
State::State(const StartConds *sc)
{
	coords = new Coordinates(sc->getCoords());
	V = sc->V;
	mu = sc->mu;
	Theta = sc->Theta;
}


void State::update(const Coordinates *cs, double velo, double mu, double Theta)
{
	static bool first = true;
	if (first)
	{
		coords = new Coordinates(cs);
		first = false;
		return;
	}

	coords->update(cs);
	V = velo;
	this->mu = mu;
	this->Theta = Theta;
}


ostream& operator <<(ostream &os, const State &s)
{
	os << "Current state:"
				"\n - " << *s.coords
		 << "\n - V, m/s: " << s.V
		 << "\n - mu: " << s.mu
		 << "\n - Theta, deg: " << Funcs::rad2deg(s.Theta) << '\n';
	return os;
}
