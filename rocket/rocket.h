#ifndef ROCKET_H
#define ROCKET_H

#include "rocket_types.h"

#include <iostream>


class Rocket
{
public:
	Rocket();
	Rocket(const StartConds &sc, const Parameters &p, const Constraints &cs,
				 const Engine &en, const Compartment *prts, int parts_num);
	~Rocket();

	friend std::ostream& operator <<(std::ostream &os, const Rocket &r);

protected:
	StartConds *sConds;				// Starting conditions
	State *state;							// Current rocket's state
	Parameters *param;				// Common rocket's parameters
	int partsN;								// Amount of compartments
	Compartment *parts;				// Rocket's compartments
	Engine *engine;						// Rocket's engine
	Constraints *constraint;	// Constraints of flight

	double mass;							// Rocket's mass
};

#endif // ROCKET_H
