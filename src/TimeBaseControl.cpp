#include "TimeBaseControl.h"
#include "HantekDataSource.h"

#include "Helpers.h"

#include <QLabel>
#include <QPushButton>
#include <QDial>

#include <QCommonStyle>
#include <QGridLayout>

TimeBaseControl::TimeBaseControl(QString title, HantekDataSource * device, QWidget *parent)
  : QGroupBox(title, parent),
    device_(device)
{
  timeBaseLabel_ = new QLabel;
  timeBaseLabel_->setAlignment(Qt::AlignHCenter);
  timeBaseLabel_->setFont(QFont("Courier", 16, QFont::Bold));

  timeBaseDial_ = new QDial;
  timeBaseDial_->setWrapping(false);
  timeBaseDial_->setNotchesVisible(true);
  timeBaseDial_->setMinimum(int(HantekDataSource::TimeBase_t::TB_MIN));
  timeBaseDial_->setMaximum(int(HantekDataSource::TimeBase_t::TB_MAX));
  timeBaseDial_->setInvertedAppearance(true);
  timeBaseDial_->setInvertedControls(true);
  timeBaseDial_->setTracking(true);

  QObject::connect(timeBaseDial_, SIGNAL(valueChanged(int)), this, SLOT(setTimeBase(int)));

  QCommonStyle style;

  QPushButton *btnInc = new QPushButton;
  btnInc->setIcon(style.standardIcon(QStyle::SP_ArrowLeft));
  btnInc->setIconSize(QSize(24, 24));
  btnInc->setAutoRepeat(true);
  QObject::connect(btnInc, SIGNAL(clicked()), this, SLOT(incTimeBase()));

  QPushButton *btnDec = new QPushButton;
  btnDec->setIcon(style.standardIcon(QStyle::SP_ArrowRight));
  btnDec->setIconSize(QSize(24, 24));
  btnDec->setAutoRepeat(true);
  QObject::connect(btnDec, SIGNAL(clicked()), this, SLOT(decTimeBase()));

  // Layout
  QGridLayout * grid = new QGridLayout(this);
  grid->setContentsMargins(QMargins());
  grid->addWidget(timeBaseLabel_, 0, 0, 1, 2, Qt::AlignHCenter | Qt::AlignBottom);
  grid->addWidget(btnInc, 1, 0, Qt::AlignCenter);
  grid->addWidget(btnDec, 1, 1, Qt::AlignCenter);
  grid->addWidget(timeBaseDial_, 2, 0, 1, 2);
  grid->setRowStretch(2, 1);
  grid->setRowMinimumHeight(0, 32);

  setLayout(grid);
}

void TimeBaseControl::incTimeBase()
{
  int tb = timeBaseDial_->value();
  if (tb < int(HantekDataSource::TimeBase_t::TB_MAX))
  {
    timeBaseDial_->setValue(tb + 1);
  }
}

void TimeBaseControl::decTimeBase()
{
  int tb = timeBaseDial_->value();
  if (tb > int(HantekDataSource::TimeBase_t::TB_MIN))
  {
    timeBaseDial_->setValue(tb - 1);
  }
}

void TimeBaseControl::setTimeBase(int value)
{
  HantekDataSource::TimeBase_t tb = HantekDataSource::TimeBase_t(value);

  timeBaseDial_->setValue(value);
  timeBaseLabel_->setText(HantekDataSource::timeBaseToString(tb));
  device_->setTimeBase(tb);

  emit valueChanged(value);
}
