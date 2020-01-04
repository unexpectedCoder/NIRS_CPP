#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QGroupBox>
#include <QComboBox>
#include <QLabel>
#include <QSpinBox>

#include "annealing/optimizer.h"
#include "annealingsettings.h"
#include "annealing/optim_funcs.h"


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  void setConnects();
  void setStandardFunc();

private:
  Ui::MainWindow *ui;
  QWidget *centralWgt;
  QPushButton *pbSetOpti;
  QPushButton *pbInit;
  QPushButton *pbShowOptimizer;
  QPushButton *pbExit;
  QBoxLayout *vButtonLay;

  QComboBox *cbStandardFuncs;
  QCheckBox *chbStandardFuncs;
  QSpinBox *spinUsrFuncDim;

  AnnealingSettings *dial;
  Bounds *bounds;
  Options *options;
  Optimizer *optimizer;

  OptimFuncsEnum funcType;
  int dim;
  double (*func)(const Vals&);

  bool isOptionsBounds;
  bool isFunc;
  bool isStandardFunc;

private slots:
  void pbSetOptClicked();
  void pbExitClicked();
  void applySettings();
  void setUsingStandartFunc();
  void initOptimizer();
  void showOptimizer();

signals:
  void wantExit();
};

#endif // MAINWINDOW_H
