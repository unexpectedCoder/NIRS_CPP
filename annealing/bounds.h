#ifndef BOUNDS_H
#define BOUNDS_H

#include <QVector>
#include <iostream>


struct Bounds
{
  // Saves boundaries of target function arguments.
  double *bmin, *bmax;		// Minimum and maximum values
  int dim;                // Dimension of target function

  Bounds() {}
  Bounds(const QVector<double> &bmin, const QVector<double> &bmax);
  Bounds(const Bounds &b);
  Bounds(const Bounds *b);
  ~Bounds();

  void set(const QVector<double> &bmin, const QVector<double> &bmax);
  bool isEmpty() const;

  friend std::ostream& operator<<(std::ostream &os, const Bounds &b);
  Bounds& operator =(const Bounds &b);
};

#endif // BOUNDS_H
