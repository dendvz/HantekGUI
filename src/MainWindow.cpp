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

// ##########################################################
//  QPushButton *btnAcquire = new QPushButton("Acquire");
//  QObject::connect(btnAcquire, SIGNAL(clicked()), this, SLOT(DoAcquire()));
//  mainLayout->addWidget(btnAcquire);
// ####################################################

  QVBoxLayout * controlPanelLayout = new QVBoxLayout;

  controlPanelLayout->addWidget(createHorizontalControl(), Qt::AlignTop);
  controlPanelLayout->addWidget(createTriggerControl(), Qt::AlignTop);
  for (int trace = 0; trace < 2; ++trace)
  {
     controlPanelLayout->addWidget(createChannelControl(trace), Qt::AlignTop);
  }

  mainLayout->addLayout(controlPanelLayout);

  setLayout(mainLayout);
//  mainLayout->addWidget(&controlPanel);
}

MainWindow::~MainWindow()
{
}

QGroupBox * MainWindow::createHorizontalControl()
{
  QGroupBox *groupBox = new QGroupBox(tr("Horizontal"));

  timeBaseLabel_ = new QLabel;
  timeBaseLabel_->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);

  timeBaseDial_ = new QDial;
  timeBaseDial_->setWrapping(false);
  timeBaseDial_->setNotchesVisible(true);
  timeBaseDial_->setMinimum(int(HantekDataSource::TimeBase::TB_MIN));
  timeBaseDial_->setMaximum(int(HantekDataSource::TimeBase::TB_MAX));

  QObject::connect(timeBaseDial_, SIGNAL(sliderMoved(int)), this, SLOT(updateTimeBase(int)));
  updateTimeBase(int(HantekDataSource::TimeBase::TB_MIN));

  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->addWidget(timeBaseLabel_);
  vbox->addWidget(timeBaseDial_);
  groupBox->setLayout(vbox);

  return groupBox;
}

QGroupBox * MainWindow::createTriggerControl()
{
  QGroupBox *groupBox = new QGroupBox(tr("Trigger"));
  QPushButton *btnDummy = new QPushButton("Dummy");

  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->addWidget(btnDummy);
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
  device_->setTriggerMode(HantekDataSource::TriggerMode::SINGLE);
  device_->Acquire();
}

void MainWindow::updateTimeBase(int tb)
{
  timeBaseLabel_->setText(HantekDataSource::timeBaseToString(HantekDataSource::TimeBase(tb)));
}
