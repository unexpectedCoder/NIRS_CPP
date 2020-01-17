#include "rocket.h"


Rocket::Rocket()
{
	sConds = nullptr;
	state = nullptr;
	param = nullptr;
	partsN = 0;
	parts = nullptr;
	engine = nullptr;
	constraint = nullptr;

	mass = 0.0;
}


Rocket::Rocket(const StartConds &sc, const Parameters &p, const Constraints &cs,
							 const Engine &en, const Compartment *prts, int parts_num)
{
	if (parts_num < 1)
		throw "Error in <Rocket>: amount of compartments must be > 0!";
	if (prts == nullptr)
		throw "Error in <Rocket>: array of compartments is empty!";

	sConds = new StartConds(sc);
	state = new State(sConds);
	param = new Parameters(p);
	engine = new Engine(en);
	constraint = new Constraints(cs);

	mass = 0.0;

	partsN = parts_num;
	parts = new Compartment[partsN];
	for (int i = 0; i < partsN; ++i)
	{
		parts[i] = prts[i];
		mass += parts[i].mass;
	}
}


Rocket::~Rocket()
{
	if (sConds == nullptr) delete sConds;
	if (state == nullptr) delete state;
	if (param == nullptr) delete param;
	if (engine == nullptr) delete engine;
	if (constraint == nullptr) delete constraint;
	if (parts != nullptr) delete [] parts;
}


std::ostream& operator <<(std::ostream &os, const Rocket &r)
{
	os << "Rocket:\n"
				" - " << *r.sConds
		 << " - " << *r.state
		 << " - " << *r.param
		 << " - " << *r.engine
		 << " - " << *r.constraint
		 << "Compartments (" << r.partsN << "):\n";
	for (int i = 0; i < r.partsN; ++i)
		os << " - " << r.parts[i];
	os << " - Mass, kg: " << r.mass << '\n';
	return os;
}
