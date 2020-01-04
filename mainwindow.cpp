#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QString>
#include <QStringList>

#include <iostream>


using namespace std;


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  bounds = new Bounds;
  options = new Options;
  optimizer = nullptr;
  // Dialog
  dial = new AnnealingSettings(bounds, options, this);

  isOptionsBounds = false;
  isFunc = false;
  isStandardFunc = false;

  setGeometry(600, 300, 250, 350);
  setWindowTitle("Rocket Ballistics");
  // Main widget
  centralWgt = new QWidget(this);
  // Labels
  QLabel *lblStandardFuncs = new QLabel("Choose standard optimization function:");
  QLabel *lblUseDefFunc = new QLabel("User defined target function dimension:");
  // Buttons
  pbSetOpti = new QPushButton("&Optimization Settings");
  pbInit = new QPushButton("&Initialize Optimizer");
  pbShowOptimizer = new QPushButton("Sho&w Optimizer");
  pbExit = new QPushButton("&Exit");
  // Check boxes
  chbStandardFuncs = new QCheckBox("Use &standard function");
  chbStandardFuncs->setCheckState(Qt::CheckState::Unchecked);
  // Combo boxes
  cbStandardFuncs = new QComboBox;
  QStringList funcsList;
  funcsList << "Rosenbrock" << "Ackley" << "Bill" << "Booth" << "Mathias";
  cbStandardFuncs->addItems(funcsList);
  cbStandardFuncs->setEnabled(false);
  // Spin boxes
  spinUsrFuncDim = new QSpinBox;
  spinUsrFuncDim->setRange(1, 99);
  // Group boxes
  QGroupBox *gboxSettings = new QGroupBox("Settings");
  // Layouts
  QVBoxLayout *vlaySettings = new QVBoxLayout;
  vlaySettings->addWidget(pbSetOpti);
  vlaySettings->addWidget(chbStandardFuncs);
  vlaySettings->addWidget(lblStandardFuncs);
  vlaySettings->addWidget(cbStandardFuncs);
  QHBoxLayout *hlaySettings = new QHBoxLayout;
  hlaySettings->addWidget(lblUseDefFunc);
  hlaySettings->addWidget(spinUsrFuncDim);
  vlaySettings->addLayout(hlaySettings);
  vlaySettings->addWidget(pbInit);
  vlaySettings->addWidget(pbShowOptimizer);
  gboxSettings->setLayout(vlaySettings);

  vButtonLay = new QBoxLayout(QBoxLayout::TopToBottom);
  vButtonLay->addWidget(gboxSettings);
  vButtonLay->addStretch(1);
  vButtonLay->addWidget(pbExit);

  centralWgt->setLayout(vButtonLay);
  setCentralWidget(centralWgt);

  // Connections
  setConnects();
}


MainWindow::~MainWindow()
{
  delete ui;
  if (optimizer != nullptr) delete optimizer;
}


void MainWindow::setConnects()
{
  // Optimization settings
  connect(pbSetOpti, &QPushButton::clicked, this, &MainWindow::pbSetOptClicked);
  connect(pbExit, &QPushButton::clicked, this, &MainWindow::pbExitClicked);
  connect(dial, &AnnealingSettings::ready, this, &MainWindow::applySettings);
  // Standard funcs
  connect(chbStandardFuncs, &QCheckBox::stateChanged, this, &MainWindow::setUsingStandartFunc);
  // Init
  connect(pbInit, &QPushButton::clicked, this, &MainWindow::initOptimizer);
  // Show
  connect(pbShowOptimizer, &QPushButton::clicked, this, &MainWindow::showOptimizer);
}


void MainWindow::setStandardFunc()
{
  int i = cbStandardFuncs->currentIndex();
  switch (i)
  {
  case 0:
    funcType = OF_ROZEN;
    func = OptimFuncs::rozen;
    dim = 2;
    break;
  case 1:
    funcType = OF_ACKLEY;
    func = OptimFuncs::ackley;
    dim = 2;
    break;
  case 2:
    funcType = OF_BILL;
    func = OptimFuncs::bill;
    dim = 2;
    break;
  case 3:
    funcType = OF_BOOTH;
    func = OptimFuncs::booth;
    dim = 2;
    break;
  case 4:
    funcType = OF_MATHIAS;
    func = OptimFuncs::mathias;
    dim = 2;
    break;
  }
}


void MainWindow::pbSetOptClicked()
{
  dial->show();
}


void MainWindow::pbExitClicked()
{
  emit wantExit();
}


void MainWindow::applySettings()
{
  isOptionsBounds = true;
}


void MainWindow::setUsingStandartFunc()
{
  if (chbStandardFuncs->isChecked())
  {
    cbStandardFuncs->setEnabled(true);
    spinUsrFuncDim->setEnabled(false);
    isStandardFunc = true;
  }
  else
  {
    cbStandardFuncs->setEnabled(false);
    spinUsrFuncDim->setEnabled(true);
    isStandardFunc = false;
  }
}


void MainWindow::initOptimizer()
{
  if (chbStandardFuncs->isChecked())
    setStandardFunc();
  else
    dim = spinUsrFuncDim->text().toInt();

  if (dim != bounds->dim)
  {
    QMessageBox::warning(this, "Optimizer Initialization",
                         "Dimension of boundaries is not equal to target function dimension!\n"
                         "Please, reset boundaries or target function!");
    return;
  }

  isFunc = true;
  optimizer = new Optimizer(func, dim, bounds, options);
  // TODO: target function
}


void MainWindow::showOptimizer()
{
  if (!isOptionsBounds || !isFunc)
  {
    QMessageBox::warning(this, "Show Optimizer",
                         "Boundaries, options or target function are not set!");
    return;
  }

  int d = optimizer->getDimension();
  Bounds *bnds = new Bounds(optimizer->getBounds());
  Options *opt = new Options(optimizer->getOptions());

  QString funcName;
  if (isStandardFunc)
    switch (funcType)
    {
    case OF_ROZEN: funcName = "<Rosenbrock>"; break;
    case OF_ACKLEY: funcName = "<Ackley>"; break;
    case OF_BILL: funcName = "<Bill>"; break;
    case OF_BOOTH: funcName = "<Booth>"; break;
    case OF_MATHIAS: funcName = "<Mathias>"; break;
    }
  else
    funcName = "<User Defined Func>";

  QString mess =
      "Target function: " + funcName +
      "\nTarget function dimension: " + QString::number(d) +
      "\n\nBoundaries:";
  for (int i = 0; i < d; ++i)
    mess += "\n - x" + QString::number(i + 1) + ": (" +
        QString::number(bnds->bmin[i]) + "; " + QString::number(bnds->bmax[i]) + ")";
  mess += "\n\nOptions:"
      "\n - start temperature: " + QString::number(opt->tStart) +
      "\n - end temperature: " + QString::number(opt->tEnd) +
      "\n - temperature reduce coefficien: " + QString::number(opt->reduce) +
      "\n - max amount of iterations: " + QString::number(opt->maxIters) +
      "\n - amount of threads: " + QString::number(opt->nThreads);

  QMessageBox::information(this, "Show Optimizer", mess);
}
