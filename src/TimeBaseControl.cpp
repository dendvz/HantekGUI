#include "TimeBaseControl.h"
#include "HantekDataSource.h"
#include "SpinCombo.h"

#include "Helpers.h"

#include <QVBoxLayout>

namespace
{
QString hScaleToString(HantekDataSource::HScale_t hScale)
{
  qreal value = HantekDataSource::hScaleToValue(hScale);

  if (value * 1e3 >= 1.0)
  {
    return QString("%1 ms").arg(value * 1e3);
  }
  else if (value * 1e6 >= 1.0)
  {
    return QString("%1 us").arg(value * 1e6);
  }
  return QString("%1 ns").arg(value * 1e9);
}


} // namespace

TimeBaseControl::TimeBaseControl(QWidget * parent, QString title, HantekDataSource * device)
  : QGroupBox(title, parent),
    device_(device)
{
  QStringList supportedTimeBases;
  for (int value = int(HantekDataSource::HScale_t::HS_MIN); value <= int(HantekDataSource::HScale_t::HS_MAX); ++value)
  {
    supportedTimeBases.append(hScaleToString(HantekDataSource::HScale_t(value)));
  }
  timebase_ = new SpinCombo(supportedTimeBases, this);
  connect(timebase_, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));

  // Layout
  QVBoxLayout * layout = new QVBoxLayout(this);
  layout->setContentsMargins(QMargins());
  layout->addWidget(timebase_);
  setLayout(layout);
}

void TimeBaseControl::onValueChanged(int value)
{
  TRACE("value=%d", value);
  device_->setHScale(HantekDataSource::HScale_t(value));
  emit valueChanged(value);
}

void TimeBaseControl::setTimeBase(int value)
{
  timebase_->set(value);
  device_->setHScale(HantekDataSource::HScale_t(value));
}
