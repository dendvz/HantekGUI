#include "SpinCombo.h"
#include "ConstrainedSpinBox.h"

#include "Helpers.h"

#include <QDial>
#include <QVBoxLayout>

SpinCombo::SpinCombo(QWidget * parent, const QStringList & items)
  : QWidget(parent),
    items_(items),
    spinBox_(new ConstrainedSpinBox(parent, items)),
    dial_(new QDial)
{
  dial_->setWrapping(false);
  dial_->setNotchesVisible(true);
  dial_->setTracking(true);
  dial_->setRange(0, items.size() - 1);

  QObject::connect(dial_, SIGNAL(valueChanged(int)), this, SLOT(onDialValueChanged(int)));
  QObject::connect(spinBox_, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxValueChanged(int)));

  QVBoxLayout * layout = new QVBoxLayout(this);
  layout->addWidget(spinBox_);
  layout->addWidget(dial_);
  setLayout(layout);
}

void SpinCombo::set(int value)
{
  spinBox_->setValue(value);
}

void SpinCombo::onDialValueChanged(int value)
{
  if (spinBox_->value() != value)
  {
    spinBox_->setValue(value);
    emit valueChanged(value);
  }
}

void SpinCombo::onSpinBoxValueChanged(int value)
{
  if (dial_->value() != value)
  {
    dial_->setValue(value);
    emit valueChanged(value);
  }
}

