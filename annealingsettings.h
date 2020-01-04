#ifndef ANNEALINGSETTINGS_H
#define ANNEALINGSETTINGS_H

#include <QDialog>
#include <QGroupBox>
#include <QBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QVector>
#include <QComboBox>

#include "annealing/bounds.h"
#include "annealing/options.h"


namespace Ui {
class AnnealingSettings;
}


class AnnealingSettings : public QDialog
{
  Q_OBJECT

public:
  explicit AnnealingSettings(Bounds *bnds, Options *opts, QWidget *parent = nullptr);
  ~AnnealingSettings();

private:
  void setConnects();

private:
  Ui::AnnealingSettings *ui;
  QWidget *wgt;
  QGroupBox *gboxOpts, *gboxBnds;
  QBoxLayout *vLay, *hLay;
  QPushButton *pbOk, *pbCancel;
  QSpinBox *sboxThreads;
  QLineEdit *lSTemp, *lFTemp;
  QLineEdit *lReduce, *lIters;
  QPushButton *pbAddBound, *pbRmBound;
  QLabel *lblBounds;

  int count;
  QLineEdit *lXmin, *lXmax;

  QVector<double> xmin, xmax;
  Bounds *bounds;
  Options *options;

public slots:
  void addBound();
  void rmBound();
  void pbOkClicked();
  void pbCancelClicked();

signals:
  void ready();
};

#endif // ANNEALINGSETTINGS_H
