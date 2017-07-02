/****************************************************************************
**
****************************************************************************/

#include "MainWindow.h"
#include "Helpers.h"

#include "HantekDataSource.h"

#include <QLineSeries>
#include <QChart>
#include <QChartView>
#include <QValueAxis>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLabel>
#include <QPushButton>
#include <QDial>
#include <QGroupBox>
#include <QTextStream>
#include <QTimer>

QT_CHARTS_USE_NAMESPACE

class CustomAxis : public QValueAxis
{
public:
  CustomAxis(qreal min, qreal max, int divisions)
  {
    setRange(min, max);
    setLabelsVisible(false);
    setTickCount(divisions + 1);
    setMinorTickCount(4);
    setMinorGridLinePen(QPen(QBrush(QColor(255, 255, 255, 31)), 0, Qt::DotLine));
  }
};

MainWindow::MainWindow(QWidget *parent)
  : QWidget(parent),
    chart_(new QChart),
    device_(nullptr)
{
  QChartView *chartView = new QChartView;
  chartView->setChart(chart_);
  chartView->setMinimumSize(800, 600);

  chart_->setBackgroundBrush(QColor(0, 0, 0, 255));
  chart_->setMargins(QMargins());

  chart_->addAxis(new CustomAxis(0, 2000, 10), Qt::AlignBottom);
  chart_->addAxis(new CustomAxis(0, 2000, 10), Qt::AlignTop);
  chart_->addAxis(new CustomAxis(-1, 1, 8),    Qt::AlignLeft);
  chart_->addAxis(new CustomAxis(-1, 1, 8),    Qt::AlignRight);

  for (int trace = 0; trace < 2; ++trace)
  {
    traces_.push_back(new QLineSeries);
    if (trace == 0)
    {
      traces_[trace]->setPen(QColor(255, 255, 0, 255));
    }
    else
    {
      traces_[trace]->setPen(QColor(0, 255, 255, 255));
    }
    chart_->addSeries(traces_[trace]);
    traces_[trace]->attachAxis(chart_->axisX());
    traces_[trace]->attachAxis(chart_->axisY());
  }

  chart_->legend()->hide();

  device_ = new HantekDataSource(traces_, this);

  QTimer * timer = new QTimer(this);
  QObject::connect(timer, SIGNAL(timeout()), this, SLOT(doAcquire()));
  timer->start(100);

  QHBoxLayout * mainLayout = new QHBoxLayout;
  mainLayout->setContentsMargins(QMargins());
  mainLayout->addWidget(chartView, 1);

  QFrame * controlPanel = new QFrame;
  mainLayout->addWidget(controlPanel);

  QVBoxLayout * controlPanelLayout = new QVBoxLayout(controlPanel);
//  controlPanelLayout->setContentsMargins(QMargins());

  controlPanelLayout->addWidget(createTimeBaseControl(), 1, Qt::AlignTop);
  controlPanelLayout->addWidget(createTriggerControl());
  for (int trace = 0; trace < 2; ++trace)
  {
     controlPanelLayout->addWidget(createChannelControl(trace));
  }

//  mainLayout->addLayout(controlPanelLayout);

  setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
}

QGroupBox * MainWindow::createTimeBaseControl()
{
  QGroupBox *groupBox = new QGroupBox(tr("Timebase"));

  timeBaseLabel_ = new QLabel;
  timeBaseLabel_->setAlignment(Qt::AlignHCenter);
  timeBaseLabel_->setFont(QFont("Courier", 16, QFont::Bold));

  timeBaseDial_ = new QDial;
  timeBaseDial_->setWrapping(false);
  timeBaseDial_->setNotchesVisible(true);
  timeBaseDial_->setMinimum(int(HantekDataSource::TimeBase_t::TB_MIN));
  timeBaseDial_->setMaximum(int(HantekDataSource::TimeBase_t::TB_MAX));
  timeBaseDial_->setTracking(true);

  QObject::connect(timeBaseDial_, SIGNAL(valueChanged(int)), this, SLOT(updateTimeBase(int)));
  updateTimeBase(int(HantekDataSource::TimeBase_t::TB_MIN));

  QPushButton *btnDec = new QPushButton("-");
  btnDec->setMaximumWidth(40);
  QObject::connect(btnDec, SIGNAL(clicked()), this, SLOT(decTimeBase()));

  QPushButton *btnInc = new QPushButton("+");
  btnInc->setMaximumWidth(40);
  QObject::connect(btnInc, SIGNAL(clicked()), this, SLOT(incTimeBase()));

  // Layout
  QGridLayout * grid = new QGridLayout;
  grid->setContentsMargins(QMargins());
  grid->addWidget(timeBaseLabel_, 0, 0, 1, 2);
  grid->addWidget(btnDec, 1, 0, Qt::AlignCenter);
  grid->addWidget(btnInc, 1, 1, Qt::AlignCenter);
  grid->addWidget(timeBaseDial_, 2, 0, 1, 2);
  grid->setRowStretch(2, 1);
  groupBox->setLayout(grid);

  return groupBox;
}

QGroupBox * MainWindow::createTriggerControl()
{
  QGroupBox *groupBox = new QGroupBox(tr("Trigger"));

  QPushButton *btnAcquire = new QPushButton("Acquire");
  QObject::connect(btnAcquire, SIGNAL(clicked()), this, SLOT(doAcquire()));

  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->addWidget(btnAcquire);
  groupBox->setLayout(vbox);

  return groupBox;
}

QGroupBox * MainWindow::createChannelControl(int ch)
{
  QString title;
  QTextStream(&title) << "Ch" << (ch + 1);
  QGroupBox *groupBox = new QGroupBox(title);
  QPushButton *btnDummy = new QPushButton("Dummy");

  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->addWidget(btnDummy);
  groupBox->setLayout(vbox);

  return groupBox;
}

void MainWindow::doAcquire()
{
  device_->setTriggerMode(HantekDataSource::TriggerMode_t::SINGLE);
  device_->Acquire();
}

void MainWindow::updateTimeBase(int tb)
{
  timeBaseLabel_->setText(HantekDataSource::timeBaseToString(HantekDataSource::TimeBase_t(tb)));
}

void MainWindow::incTimeBase()
{
  int tb = timeBaseDial_->value();
  if (tb < int(HantekDataSource::TimeBase_t::TB_MAX))
  {
    timeBaseDial_->setValue(tb + 1);
  }
}

void MainWindow::decTimeBase()
{
  int tb = timeBaseDial_->value();
  if (tb > int(HantekDataSource::TimeBase_t::TB_MIN))
  {
    timeBaseDial_->setValue(tb - 1);
  }
}

