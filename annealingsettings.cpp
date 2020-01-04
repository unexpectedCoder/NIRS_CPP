#include "annealingsettings.h"
#include "ui_annealingsettings.h"

#include <QString>
#include <QMessageBox>

#include <iostream>


using namespace std;


AnnealingSettings::AnnealingSettings(Bounds *bnds, Options *opts,
                                     QWidget *parent) :
  QDialog(parent),
  ui(new Ui::AnnealingSettings)
{
  bounds = bnds;
  options = opts;

  ui->setupUi(this);
  setWindowTitle("Optimization Settings");
  setFixedWidth(300);
  setFixedHeight(400);

  // Main widget
  wgt = new QWidget(this);
  // Spin box
  spinThreads = new QSpinBox;
  spinThreads->setMinimum(1);
  spinThreads->setMaximumWidth(80);
  // Group box
  gboxOpts = new QGroupBox("Options");
  gboxBnds = new QGroupBox("Boundaries");
  // Buttons
  pbAddBound = new QPushButton("&Add");
  pbRmBound = new QPushButton("&Remove");
  pbOk = new QPushButton("&Ok");
  pbCancel = new QPushButton("&Cancel");
  // Layouts
  vLay = new QBoxLayout(QBoxLayout::TopToBottom);
  hLay = new QBoxLayout(QBoxLayout::LeftToRight);
  // Options UI
  QBoxLayout * vlayOpts = new QBoxLayout(QBoxLayout::TopToBottom);
  QLabel *lblThreads = new QLabel("Amount\nof threads:");
  QBoxLayout *hlayThread = new QBoxLayout(QBoxLayout::LeftToRight);
  hlayThread->addWidget(lblThreads);
  hlayThread->addStretch(1);
  hlayThread->addWidget(spinThreads);
  QLabel *lblSTemp = new QLabel("Start temp:");
  QBoxLayout *hlaySTemp = new QBoxLayout(QBoxLayout::LeftToRight);
  lSTemp = new QLineEdit;
  lSTemp->setMaximumWidth(80);
  hlaySTemp->addWidget(lblSTemp);
  hlaySTemp->addStretch(1);
  hlaySTemp->addWidget(lSTemp);
  QLabel *lblFTemp = new QLabel("Finish temp:");
  QBoxLayout *hlayFTemp = new QBoxLayout(QBoxLayout::LeftToRight);
  lFTemp = new QLineEdit;
  lFTemp->setMaximumWidth(80);
  hlayFTemp->addWidget(lblFTemp);
  hlayFTemp->addStretch(1);
  hlayFTemp->addWidget(lFTemp);
  QLabel *lblReduce = new QLabel("Reduce coeff:");
  QBoxLayout *hlayReduce = new QBoxLayout(QBoxLayout::LeftToRight);
  lReduce = new QLineEdit;
  lReduce->setMaximumWidth(80);
  hlayReduce->addWidget(lblReduce);
  hlayReduce->addStretch(1);
  hlayReduce->addWidget(lReduce);
  QLabel *lblIters = new QLabel("Maximum number\nof iterations:");
  QBoxLayout *hlayIters = new QBoxLayout(QBoxLayout::LeftToRight);
  lIters = new QLineEdit;
  lIters->setMaximumWidth(80);
  hlayIters->addWidget(lblIters);
  hlayIters->addStretch(1);
  hlayIters->addWidget(lIters);
  vlayOpts->addLayout(hlayThread);
  vlayOpts->addLayout(hlaySTemp);
  vlayOpts->addLayout(hlayFTemp);
  vlayOpts->addLayout(hlayReduce);
  vlayOpts->addLayout(hlayIters);
  gboxOpts->setLayout(vlayOpts);
  // Boundaries UI
  count = 0;
  QBoxLayout *vlayBounds = new QBoxLayout(QBoxLayout::TopToBottom);
  QBoxLayout *hlayBounds = new QBoxLayout(QBoxLayout::LeftToRight);
  QBoxLayout *hlayBoundsButton = new QBoxLayout(QBoxLayout::LeftToRight);
  lblBounds = new QLabel("#" + QString::number(count));
  QLabel *lblMin = new QLabel("Min:");
  QLabel *lblMax = new QLabel("Max:");
  lXmin = new QLineEdit;
  lXmax = new QLineEdit;
  hlayBounds->addWidget(lblBounds);
  hlayBounds->addWidget(lblMin);
  hlayBounds->addWidget(lXmin);
  hlayBounds->addWidget(lblMax);
  hlayBounds->addWidget(lXmax);
  hlayBoundsButton->addStretch(1);
  hlayBoundsButton->addWidget(pbAddBound);
  hlayBoundsButton->addWidget(pbRmBound);
  hlayBoundsButton->addStretch(1);
  vlayBounds->addLayout(hlayBounds);
  vlayBounds->addLayout(hlayBoundsButton);
  gboxBnds->setLayout(vlayBounds);

  hLay->addStretch(1);
  hLay->addWidget(pbCancel);
  hLay->addWidget(pbOk);
  hLay->addStretch(1);

  vLay->addWidget(gboxOpts);
  vLay->addStretch(1);
  vLay->addWidget(gboxBnds);
  vLay->addLayout(hLay);

  setLayout(vLay);

  // Init
  lSTemp->setText(QString::number(options->tStart));
  lFTemp->setText(QString::number(options->tEnd));
  lReduce->setText(QString::number(options->reduce));
  lIters->setText(QString::number(options->maxIters));
  lXmin->setText("-10.0");
  lXmax->setText("10.0");
  // Conections
  setConnects();
}


AnnealingSettings::~AnnealingSettings()
{
  delete ui;
}


void AnnealingSettings::setConnects()
{
  connect(pbAddBound, &QPushButton::clicked, this, &AnnealingSettings::addBound);
  connect(pbRmBound, &QPushButton::clicked, this, &AnnealingSettings::rmBound);
  connect(pbOk, &QPushButton::clicked, this, &AnnealingSettings::pbOkClicked);
  connect(pbCancel, &QPushButton::clicked, this, &AnnealingSettings::pbCancelClicked);
}


void AnnealingSettings::addBound()
{
  if (lXmin->text().isEmpty() || lXmax->text().isEmpty())
    throw "Error in <AnnealingSettings>: empty boundaries line edit!";
  double min = lXmin->text().toDouble();
  double max = lXmax->text().toDouble();
  if (min > max)
  {
    QMessageBox::warning(this, "Boundaries",
                         "Maximum boundary value must be greater than minimum!\n"
                         "State isn't changed.");
    return;
  }

  xmin.push_back(min);
  xmax.push_back(max);
  lblBounds->setText("#" + QString::number(++count));
}


void AnnealingSettings::rmBound()
{
  if (!xmin.isEmpty())
  {
    xmin.pop_back();
    xmax.pop_back();
    lblBounds->setText("#" + QString::number(--count));
  }
}


void AnnealingSettings::pbOkClicked()
{
  if (lSTemp->text().isEmpty() ||
      lFTemp->text().isEmpty() ||
      lReduce->text().isEmpty() ||
      lIters->text().isEmpty())
  {
    QMessageBox::warning(this, "Options", "Some margins are empty!");
    return;
  }
  if (xmin.isEmpty() || xmax.isEmpty())
  {
    QMessageBox::warning(this, "Bounds", "Boundaries are empty!\n"
                                         "Use 'Add' button to add boundary.");
    return;
  }
  options->tStart = lSTemp->text().toDouble();
  options->tEnd = lFTemp->text().toDouble();
  options->reduce = lReduce->text().toDouble();
  options->maxIters = lIters->text().toInt();
  options->nThreads = spinThreads->text().toInt();
  bounds->set(xmin, xmax);

  emit ready();
  close();
}

void AnnealingSettings::pbCancelClicked()
{
  close();
}
