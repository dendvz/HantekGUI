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

signals:
  void valueChanged(int value);

public slots:
  void setTimeBase(int value);

private slots:
  void onValueChanged(int value);

private:
  HantekDataSource * device_;
  SpinCombo * timebase_;
};

#endif // TIMEBASECONTROL_H
