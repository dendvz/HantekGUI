#include "SpinCombo.h"

#include <QSpinBox>
#include <QDial>

SpinCombo::SpinCombo(QWidget * parent, const QStringList & items)
  : QWidget(parent),
    items_(items),
    spinBox_(new QSpinBox),
    dial_(new QDial)
{
  dial_->setWrapping(false);
  dial_->setNotchesVisible(true);
//  dial_->setMinimum(int(HantekDataSource::TimeBase_t::TB_MIN));
//  dial_->setMaximum(int(HantekDataSource::TimeBase_t::TB_MAX));
  dial_->setTracking(true);
}


void SpinCombo::set(int value)
{
  Q_UNUSED(value)
}
