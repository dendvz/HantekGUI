#ifndef SPINCOMBO_H
#define SPINCOMBO_H

#include <QWidget>

class ConstrainedSpinBox;
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

private slots:
  void onDialValueChanged(int value);
  void onSpinBoxValueChanged(int value);

private:
  QStringList items_;
  ConstrainedSpinBox * spinBox_;
  QDial * dial_;
};

#endif // SPINCOMBO_H
