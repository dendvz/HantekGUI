#ifndef CHANNELSCALESPINBOX_H
#define CHANNELSCALESPINBOX_H

#include <QSpinBox>

class QColor;

class ConstrainedSpinBox : public QSpinBox
{
  Q_OBJECT

public:
  explicit ConstrainedSpinBox(const QStringList & items, QWidget * parent = nullptr);

  int valueFromText(const QString & text) const override;
  QString textFromValue(int value) const override;

private:
  QStringList items_;
};

#endif // CHANNELSCALESPINBOX_H
