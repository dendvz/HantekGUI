/****************************************************************************
**
****************************************************************************/

#include "MainWindow.h"
#include "Helpers.h"

#include "HantekDataSource.h"
#include "TimeBaseControl.h"

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
#include <QCommonStyle>
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
  mainLayout->setSpacing(0);
  mainLayout->addWidget(chartView, 1);

  QFrame * separator = new QFrame;
  separator->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  separator->setMinimumWidth(4);
  mainLayout->addWidget(separator);

  QFrame * controlPanel = new QFrame;
  mainLayout->addWidget(controlPanel);

  QVBoxLayout * controlPanelLayout = new QVBoxLayout(controlPanel);

  timeBaseControl_ = new TimeBaseControl(tr("Timebase"), device_, this);

  // TODO: Load from settings
  timeBaseControl_->setTimeBase(int(HantekDataSource::TimeBase_t::TB_200us));

  controlPanelLayout->addWidget(timeBaseControl_, 1, Qt::AlignTop);
  controlPanelLayout->addWidget(createTriggerControl());
  for (int trace = 0; trace < 2; ++trace)
  {
     controlPanelLayout->addWidget(createChannelControl(trace));
  }

  setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
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
