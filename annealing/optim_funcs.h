#ifndef OPTIM_FUNCS_H
#define OPTIM_FUNCS_H

#include <math.h>

#include "annealing/help_types.h"


enum OptimFuncsEnum
{
  OF_ROZEN,
  OF_ACKLEY,
  OF_BILL,
  OF_BOOTH,
  OF_MATHIAS
};


namespace OptimFuncs
{
double rozen(const Vals &x);
double ackley(const Vals &x);
double bill(const Vals &x);
double booth(const Vals &x);
double mathias(const Vals &x);
}

#endif // OPTIM_FUNCS_H
