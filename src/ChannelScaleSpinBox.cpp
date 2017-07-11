#include "ChannelScaleSpinBox.h"
#include "HantekDataSource.h"

#include <QLineEdit>
#include <QVariant>

ChannelScaleSpinBox::ChannelScaleSpinBox(QWidget * parent, QColor color)
  : QSpinBox(parent)
{
  setMinimum(int(HantekDataSource::VScale_t::VS_MIN));
  setMaximum(int(HantekDataSource::VScale_t::VS_MAX));
  setAlignment(Qt::AlignCenter);
  setMinimumWidth(150);
  setWrapping(false);

  setStyleSheet(
    "QSpinBox { border: 0px; padding: 0px; } \
     QSpinBox::up-button   { subcontrol-position: right;  width: 40px; height: 35px; } \
     QSpinBox::down-button { subcontrol-position: left;   width: 40px; height: 35px; }"
  );


  QLineEdit * entry = findChild<QLineEdit *>();
  entry->setReadOnly(true);

  // FIXME
  QVariant variant = color;
  entry->setStyleSheet("QLineEdit { background: " + variant.toString() + "; }");

  setFont(QFont("Courier", 16, QFont::Bold));
}

int ChannelScaleSpinBox::valueFromText(const QString & text) const
{
  for (int value = int(HantekDataSource::VScale_t::VS_MIN); value <= int(HantekDataSource::VScale_t::VS_MAX); ++value)
  {
    if (HantekDataSource::vScaleToString(HantekDataSource::VScale_t(value)) == text)
    {
      return value;
    }
  }
  return 0;
}

QString ChannelScaleSpinBox::textFromValue(int value) const
{
  return HantekDataSource::vScaleToString(HantekDataSource::VScale_t(value));
}
