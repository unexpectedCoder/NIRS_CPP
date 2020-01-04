#include "annealing/optim_funcs.h"


double OptimFuncs::rozen(const Vals &x)
{
  return pow(1.0 - x[0], 2.0) + 100 * pow(x[1] - x[0] * x[0], 2.0);
}


double OptimFuncs::ackley(const Vals &x)
{
  return -20 * exp(-0.2 * sqrt(0.5 * (x[0] * x[0] + x[1] * x[1]))) -
      exp(0.5 * (cos(2 * M_PI * x[0]) + cos(2 * M_PI * x[1]))) +
      exp(1) + 20.0;
}


double OptimFuncs::bill(const Vals &x)
{
  return pow(1.5 - x[0] + x[0] * x[1], 2.0) +
      pow(2.25 - x[0] + x[0] * x[1] * x[1], 2.0) +
      pow(2.625 - x[0] + x[0] * x[1] * x[1] * x[1], 2.0);
}


double OptimFuncs::booth(const Vals &x)
{
  return pow(x[0] + 2.0 * x[1] - 7.0, 2.0) +
      pow(2.0 * x[0] + x[1] - 5.0, 2.0);
}


double OptimFuncs::mathias(const Vals &x)
{
  return 0.26 * (x[0] * x[0] + x[1] * x[1]) - 0.48 * x[0] * x[1];
}
