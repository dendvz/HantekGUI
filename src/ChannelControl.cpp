#include "ChannelControl.h"
#include "HantekDataSource.h"
#include "ChannelScaleSpinBox.h"

#include "Helpers.h"

#include <QLabel>
#include <QPushButton>
#include <QDial>
#include <QSpinBox>
#include <QLineEdit>

#include <QCommonStyle>
#include <QGridLayout>

ChannelControl::ChannelControl(QWidget * parent, int index, HantekDataSource * device)
  : QGroupBox(QString("CH%1").arg(index + 1), parent),
    channelIndex_(index),
    device_(device),
    scale_(new ChannelScaleSpinBox(nullptr, QColor(255, 255, 0)))
{
  connect(scale_, SIGNAL(valueChanged(int)), this, SLOT(onScaleValueChanged()), Qt::QueuedConnection);
  // Layout
  QGridLayout * grid = new QGridLayout(this);
  grid->setContentsMargins(QMargins());
  grid->addWidget(scale_, 0, 0, 1, 2);
  grid->setRowStretch(0, 1);

  setLayout(grid);
}

void ChannelControl::onScaleValueChanged()
{
  scale_->findChild<QLineEdit *>()->deselect();
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
