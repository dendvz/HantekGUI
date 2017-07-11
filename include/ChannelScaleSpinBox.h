#ifndef CHANNELSCALESPINBOX_H
#define CHANNELSCALESPINBOX_H

#include <QSpinBox>

class QColor;

class ChannelScaleSpinBox : public QSpinBox
{
  Q_OBJECT

public:
  explicit ChannelScaleSpinBox(QWidget * parent, QColor color);

  int valueFromText(const QString & text) const override;
  QString textFromValue(int value) const override;
};

#endif // CHANNELSCALESPINBOX_H
