/****************************************************************************
**
****************************************************************************/

#include "MainWindow.h"
#include "Helpers.h"

#include "HantekDataSource.h"
#include "TimeBaseControl.h"
#include "ChannelControl.h"
#include "ScopeView.h"

#include <QSettings>

#include <QLineSeries>

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

MainWindow::MainWindow(QWidget *parent)
  : QWidget(parent),
    device_(nullptr)
{
  device_ = new HantekDataSource(this);

  ScopeView* chartView = new ScopeView(this, device_);
  chartView->setMinimumSize(800, 600);

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

  timeBaseControl_ = new TimeBaseControl(this, tr("Timebase"), device_);

  // TODO: Load from settings
  timeBaseControl_->set(int(HantekDataSource::HScale_t::HS_200us));

  controlPanelLayout->addWidget(timeBaseControl_, 1, Qt::AlignTop);
  controlPanelLayout->addWidget(createTriggerControl());
  for (int trace = 0; trace < device_->getChannelCount(); ++trace)
  {
    ChannelControl * ch = new ChannelControl(this, trace, device_);
    // TODO: Load from settings
    ch->set(int(HantekDataSource::VScale_t::VS_1V));
    controlPanelLayout->addWidget(ch);
    channelControl_.push_back(ch);
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

void MainWindow::doAcquire()
{
  device_->setTriggerMode(HantekDataSource::TriggerMode_t::SINGLE);
  device_->Acquire();
}
