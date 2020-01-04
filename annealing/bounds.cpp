#include "bounds.h"


using namespace std;


Bounds::Bounds(const QVector<double> &bmin, const QVector<double> &bmax)
{
  if (bmin.size() != bmax.size())
    throw "Error in <Bounds>: boundaries lengths are not equal to each other!";

  this->bmin = nullptr;
  this->bmax = nullptr;
  dim = bmin.size();
  if (dim > 0)
  {
    this->bmin = new double[dim];
    this->bmax = new double[dim];
    for (int i = 0; i < dim; ++i)
    {
      if (bmax[i] < bmin[i])
        throw "Error in <Bounds>: maximum of value must be > minimum of value!";
      this->bmin[i] = bmin[i];
      this->bmax[i] = bmax[i];
    }
  }
}


Bounds::Bounds(const Bounds &b)
{
  bmin = nullptr;
  bmax = nullptr;
  dim = b.dim;
  if (dim > 0)
  {
    bmin = new double[dim];
    bmax = new double[dim];
    for (int i = 0; i < dim; ++i)
    {
      bmin[i] = b.bmin[i];
      bmax[i] = b.bmax[i];
    }
  }
}


Bounds::Bounds(const Bounds *b)
{
  bmin = nullptr;
  bmax = nullptr;
  dim = b->dim;
  if (dim > 0)
  {
    bmin = new double[dim];
    bmax = new double[dim];
    for (int i = 0; i < dim; ++i)
    {
      bmin[i] = b->bmin[i];
      bmax[i] = b->bmax[i];
    }
  }
}


Bounds::~Bounds()
{
  if (bmin != nullptr) delete [] bmin;
  if (bmax != nullptr) delete [] bmax;
}


void Bounds::set(const QVector<double> &bmin, const QVector<double> &bmax)
{
  if (bmin.size() != bmax.size())
    throw "Error in <Bounds>: boundaries lengths are not equal to each other!";

  dim = bmin.size();
  if (dim > 0)
  {
    this->bmin = new double[dim];
    this->bmax = new double[dim];
    for (int i = 0; i < dim; ++i)
    {
      if (bmax[i] < bmin[i])
        throw "Error in <Bounds>: maximum of value must be > minimum of value!";
      this->bmin[i] = bmin[i];
      this->bmax[i] = bmax[i];
    }
  }
}


bool Bounds::isEmpty() const
{
  if (bmin == nullptr)
    return true;
  return false;
}


Bounds& Bounds::operator =(const Bounds &b)
{
  if (this == &b)
    return *this;
  dim = b.dim;
  if (dim > 0)
  {
    bmin = new double[dim];
    bmax = new double[dim];
    for (int i = 0; i < dim; ++i)
    {
      bmin[i] = b.bmin[i];
      bmax[i] = b.bmax[i];
    }
  }
  return *this;
}


ostream& operator<<(ostream &os, const Bounds &b)
{
  os << "BOUNDS\n";
  os << " - dimension: " << b.dim << '\n';
  for (int i = 0; i < b.dim; ++i)
    os << " - x" << i + 1 << ": (" << b.bmin[i] << "; " << b.bmax[i] << ")\n";
  return os;
}
