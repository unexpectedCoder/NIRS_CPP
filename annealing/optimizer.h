#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include <QObject>
#include <QMutex>
#include <QThread>

#include "annealing.h"


typedef QVector<Result> Results;
typedef QVector<Result>::const_iterator ResultsItr_c;


class Optimizer : public QObject
{
  Q_OBJECT

public:
  explicit Optimizer(double (*f)(const Vals&), int dim, const Bounds &bnds, const Options &opt,
                     QObject *parent = nullptr);
  explicit Optimizer(double (*f)(const Vals&), int dim, const Bounds *bnds, const Options *opt,
                     QObject *parent = nullptr);
  ~Optimizer();

  void optimize();
  int getDimension() const;
  const Bounds* getBounds() const;
  const Options* getOptions() const;

private:
  void setConnects(int i);

private:
  Annealing *annealing;

  int nThreads;
  QMutex mutex;
  QThread **threads;
  Annealing **anns;

  Result result;			// The best result from all threads
  Results results;		// Results from all threads

public slots:
  void addResult(const Result&);
  void showResults();
  void showBestResut();

signals:
  void resultAdded();
  void resultsReady();
  void completed(const Result&);
};

#endif // OPTIMIZER_H
