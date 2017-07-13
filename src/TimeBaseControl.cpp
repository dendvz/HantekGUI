#include "TimeBaseControl.h"
#include "HantekDataSource.h"
#include "ConstrainedSpinBox.h"

#include "Helpers.h"

#include <QLabel>
#include <QPushButton>
#include <QDial>
#include <QLineEdit>

#include <QCommonStyle>
#include <QGridLayout>

TimeBaseControl::TimeBaseControl(QWidget * parent, QString title, HantekDataSource * device)
  : QGroupBox(title, parent),
    device_(device)
{
  QStringList supportedTimeBases;
  for (int value = int(HantekDataSource::TimeBase_t::TB_MIN); value <= int(HantekDataSource::TimeBase_t::TB_MAX); ++value)
  {
    supportedTimeBases.append(HantekDataSource::timeBaseToString(HantekDataSource::TimeBase_t(value)));
  }
  timeBaseSpinBox_ = new ConstrainedSpinBox(supportedTimeBases);
  connect(timeBaseSpinBox_, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxValueChanged()), Qt::QueuedConnection);

  timeBaseDial_ = new QDial;
  timeBaseDial_->setWrapping(false);
  timeBaseDial_->setNotchesVisible(true);
  timeBaseDial_->setMinimum(int(HantekDataSource::TimeBase_t::TB_MIN));
  timeBaseDial_->setMaximum(int(HantekDataSource::TimeBase_t::TB_MAX));
  timeBaseDial_->setTracking(true);

  QObject::connect(timeBaseDial_, SIGNAL(valueChanged(int)), this, SLOT(setTimeBase(int)));

  // Layout
  QGridLayout * grid = new QGridLayout(this);
  grid->setContentsMargins(QMargins());
  grid->addWidget(timeBaseSpinBox_, 0, 0, 1, 2, Qt::AlignHCenter | Qt::AlignBottom);
  grid->addWidget(timeBaseDial_, 2, 0, 1, 2);
  grid->setRowStretch(2, 1);
  grid->setRowMinimumHeight(0, 32);

  setLayout(grid);
}

void TimeBaseControl::onSpinBoxValueChanged()
{
  timeBaseSpinBox_->findChild<QLineEdit *>()->deselect();

  int value = timeBaseSpinBox_->value();
  timeBaseDial_->setValue(value);
  device_->setTimeBase(HantekDataSource::TimeBase_t(value));

  emit valueChanged(value);
}

void TimeBaseControl::setTimeBase(int value)
{
  timeBaseDial_->setValue(value);
  timeBaseSpinBox_->setValue(value);
  device_->setTimeBase(HantekDataSource::TimeBase_t(value));

  emit valueChanged(value);
}
