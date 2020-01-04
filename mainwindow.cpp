#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
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
  pbExit = new QPushButton("&Exit");
  // Check boxes
  chbStandardFuncs = new QCheckBox("Use &standart function");
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
  gboxSettings->setLayout(vlaySettings);

  vButtonLay = new QBoxLayout(QBoxLayout::TopToBottom);
  vButtonLay->addWidget(gboxSettings);
  vButtonLay->addWidget(pbInit);
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
  delete dial;
  delete bounds;
  delete options;
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

  optimizer = new Optimizer(func, dim, bounds, options);
  // TODO: target function
}
