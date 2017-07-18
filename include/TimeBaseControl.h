#ifndef TIMEBASECONTROL_H
#define TIMEBASECONTROL_H

#include <QGroupBox>

class QLabel;
class QDial;
class HantekDataSource;
class SpinCombo;

class TimeBaseControl : public QGroupBox
{
  Q_OBJECT
public:
  TimeBaseControl(QWidget * parent, QString title, HantekDataSource * device);
  void set(int value);

signals:
  void valueChanged(int value);

private slots:
  void onValueChanged(int value);

private:
  HantekDataSource * device_;
  SpinCombo * timebase_;
};

#endif // TIMEBASECONTROL_H
