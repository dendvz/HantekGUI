#ifndef TIMEBASECONTROL_H
#define TIMEBASECONTROL_H

#include <QGroupBox>

class QLabel;
class ConstrainedSpinBox;
class QDial;
class HantekDataSource;

class TimeBaseControl : public QGroupBox
{
  Q_OBJECT
public:
  TimeBaseControl(QWidget * parent, QString title, HantekDataSource * device);

signals:
  void valueChanged(int value);

public slots:
  void setTimeBase(int value);

private slots:
  void onSpinBoxValueChanged();

private:
  HantekDataSource * device_;
  ConstrainedSpinBox * timeBaseSpinBox_;
  QDial  * timeBaseDial_;
};

#endif // TIMEBASECONTROL_H
