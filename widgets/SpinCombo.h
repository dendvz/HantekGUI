#ifndef SPINCOMBO_H
#define SPINCOMBO_H

#include <QWidget>

class QSpinBox;
class QDial;

class SpinCombo : public QWidget
{
  Q_OBJECT
public:
  SpinCombo(QWidget * parent, const QStringList & items);

signals:
  void valueChanged(int value);

public slots:
  void set(int value);

private:
  const QStringList & items_;
  QSpinBox * spinBox_;
  QDial * dial_;
};

#endif // SPINCOMBO_H
