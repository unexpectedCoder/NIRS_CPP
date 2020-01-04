#include "options.h"


using namespace std;


Options::Options(const Options &opt)
{
  tStart = opt.tStart;
  tEnd = opt.tEnd;
  reduce = opt.reduce;
  maxIters = opt.maxIters;
  nThreads = opt.nThreads;
}


Options::Options(const Options *opt)
{
  tStart = opt->tStart;
  tEnd = opt->tEnd;
  reduce = opt->reduce;
  maxIters = opt->maxIters;
  nThreads = opt->nThreads;
}


Options &Options::operator =(const Options &opt)
{
  if (this == &opt)
    return *this;
  tStart = opt.tStart;
  tEnd = opt.tEnd;
  reduce = opt.reduce;
  maxIters = opt.maxIters;
  nThreads = opt.nThreads;
  return *this;
}


ostream& operator <<(ostream &os, const Options &opt)
{
  os << "OPTIONS\n"
     << " - start temperature: " << opt.tStart << '\n'
     << " - end temperature: " << opt.tEnd << '\n'
     << " - temperature reduce coefficien: " << opt.reduce << '\n'
     << " - max amount of iterations: " << opt.maxIters << '\n'
     << " - amount of threads: " << opt.nThreads << '\n';
  return os;
}
