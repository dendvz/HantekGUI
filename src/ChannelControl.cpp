#include "ChannelControl.h"
#include "HantekDataSource.h"
#include "SpinCombo.h"

#include "Helpers.h"

#include <QLabel>
#include <QPushButton>
#include <QDial>
#include <QSpinBox>
#include <QLineEdit>

#include <QCommonStyle>
#include <QGridLayout>

namespace
{
QString vScaleToString(HantekDataSource::VScale_t vScale)
{
  qreal value = HantekDataSource::vScaleToValue(vScale);

  switch (vScale)
  {
  case HantekDataSource::VScale_t::VS_100mV:
  case HantekDataSource::VScale_t::VS_200mV:
  case HantekDataSource::VScale_t::VS_500mV:
    return QString("%1mV").arg(value * 1000);
  case HantekDataSource::VScale_t::VS_1V:
  case HantekDataSource::VScale_t::VS_2V:
  case HantekDataSource::VScale_t::VS_5V:
    return QString("%1V").arg(value);
  }
  return QString();
}

} // namespace


ChannelControl::ChannelControl(QWidget * parent, int index, HantekDataSource * device)
  : QGroupBox(QString("CH%1").arg(index + 1), parent),
    channelIndex_(index),
    device_(device)
{
  QStringList voltageRanges;
  for (int value = int(HantekDataSource::VScale_t::VS_MIN); value <= int(HantekDataSource::VScale_t::VS_MAX); ++value)
  {
    voltageRanges.append(vScaleToString(HantekDataSource::VScale_t(value)));
  }
  voltage_ = new SpinCombo(voltageRanges, this);

  voltage_->findChild<QDial *>()->setMaximumHeight(80);

  // TODO: Load from settings
  QColor color;
  if (index == 0)
  {
    color = QColor(255, 255, 0);
  }
  else
  {
    color = QColor(0, 255, 255);
  }

  setStyleSheet(QString("QGroupBox::title { background-color: rgb(%1, %2, %3); }").arg(color.red()).arg(color.green()).arg(color.blue()));

  // Layout
  QGridLayout * grid = new QGridLayout(this);
  grid->setContentsMargins(QMargins());
  grid->addWidget(voltage_, 0, 0, 1, 2);
  grid->setRowStretch(0, 1);

  setLayout(grid);
}

void ChannelControl::onScaleValueChanged()
{
}

void ChannelControl::setScale(int value)
{
  /*
  HantekDataSource::VScale_t vs = HantekDataSource::VScale_t(value);

  scaleDial_->setValue(value);
  scaleLabel_->setText(HantekDataSource::vScaleToString(vs));
  device_->setVScale(channelIndex_, vs);

  emit valueChanged(value);
  */
}
