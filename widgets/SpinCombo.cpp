#include "SpinCombo.h"
#include "ConstrainedSpinBox.h"

#include "Helpers.h"

#include <QDial>
#include <QVBoxLayout>
#include <QLineEdit>

SpinCombo::SpinCombo(const QStringList & items, QWidget * parent)
  : QWidget(parent),
    items_(items),
    spinBox_(new ConstrainedSpinBox(items, parent)),
    dial_(new QDial)
{
  dial_->setWrapping(false);
  dial_->setNotchesVisible(true);
  dial_->setTracking(true);
  dial_->setRange(0, items.size() - 1);

  QObject::connect(dial_, SIGNAL(valueChanged(int)), this, SLOT(onDialValueChanged(int)));
  QObject::connect(spinBox_, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxValueChanged(int)), Qt::QueuedConnection);

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
  spinBox_->setValue(value);
  emit valueChanged(value);
}

void SpinCombo::onSpinBoxValueChanged(int value)
{
  spinBox_->findChild<QLineEdit *>()->deselect();
  dial_->setValue(value);
}

