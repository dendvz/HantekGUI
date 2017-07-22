#include "ChannelControl.h"
#include "HantekDataSource.h"
#include "SpinCombo.h"

#include "Helpers.h"

#include <QFrame>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QDial>

#include <QCommonStyle>
#include <QGridLayout>
#include <QVBoxLayout>

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
  QString rgb = device_->getConfig(QString("CH%1/color").arg(index + 1)).toString();
  setStyleSheet(
    "QGroupBox { border: 5px solid " + rgb + "; border-radius: 10px; margin-top: 1ex; }\
     QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top center; padding: 0 3px; }"
  );

  QStringList voltageRanges;
  for (int value = int(HantekDataSource::VScale_t::VS_MIN); value <= int(HantekDataSource::VScale_t::VS_MAX); ++value)
  {
    voltageRanges.append(vScaleToString(HantekDataSource::VScale_t(value)));
  }
  voltage_ = new SpinCombo(this, voltageRanges);
  voltage_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  // TODO: show / hide controls via settings
  bool isKnobVisible = true;
  bool isProbeVisible = true;
  bool isInputVisible = false;

  if (isKnobVisible)
  {
    voltage_->findChild<QDial *>()->setMaximumHeight(80);
  }
  else
  {
    voltage_->findChild<QDial *>()->setVisible(false);
  }

  connect(voltage_, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));

  // Layout
  QVBoxLayout * layout = new QVBoxLayout(this);
  layout->addWidget(voltage_);

  QGridLayout * grid = new QGridLayout;

  int row = 0;
  if (isProbeVisible)
  {
    QLabel * probeLabel = new QLabel("Probe:");
    grid->addWidget(probeLabel, row, 0, 1, 1, Qt::AlignRight);

    probe_ = new QComboBox(this);
    probe_->addItems(QStringList({"x1", "x10"}));
    probe_->setFont(QFont("Courier", 14, QFont::Bold));
    probe_->setFocusPolicy(Qt::StrongFocus);
    grid->addWidget(probe_, row, 1);
    ++row;
  }

  if (isInputVisible)
  {
    QLabel * inputLabel = new QLabel("Input:");
    grid->addWidget(inputLabel, row, 0, 1, 1, Qt::AlignRight);

    input_ = new QComboBox(this);
    input_->addItems(QStringList({"DC", "AC", "GND"}));
    input_->setFont(QFont("Courier", 14, QFont::Bold));
    input_->setFocusPolicy(Qt::StrongFocus);
    grid->addWidget(input_, row, 1);
    ++row;
  }

  layout->addLayout(grid);
  setLayout(layout);
}

void ChannelControl::onValueChanged(int value)
{
  device_->setVScale(channelIndex_, HantekDataSource::VScale_t(value));
}

void ChannelControl::set(int value)
{
  voltage_->set(value);
  device_->setVScale(channelIndex_, HantekDataSource::VScale_t(value));
}
