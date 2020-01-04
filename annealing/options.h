#ifndef OPTIONS_H
#define OPTIONS_H

#include <iostream>


struct Options
{
  // Saves the algorithm options.
  double tStart, tEnd;		// Temperatures at the beginning and in the end
  double reduce;					// Cooling coefficient
  int maxIters;						// Maximum amount of iterations
  int nThreads;           // Amount of threads

  Options(double t_start = 50000.0, double t_end = 0.001,
          double r = 0.99, int iters = 1000000, int threads = 1) :
    tStart(t_start), tEnd(t_end), reduce(r), maxIters(iters), nThreads(threads)
  {}
  Options(const Options &opt);
  Options(const Options *opt);

  Options& operator =(const Options &opt);
  friend std::ostream& operator <<(std::ostream &os, const Options &opt);
};

#endif // OPTIONS_H
