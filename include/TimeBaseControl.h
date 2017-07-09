#ifndef TIMEBASECONTROL_H
#define TIMEBASECONTROL_H

#include <QGroupBox>

class QLabel;
class QDial;
class HantekDataSource;

class TimeBaseControl : public QGroupBox
{
  Q_OBJECT
public:
  explicit TimeBaseControl(QString title, HantekDataSource * device, QWidget *parent = nullptr);

signals:
  void valueChanged(int value);

public slots:
  void setTimeBase(int value);

private slots:
  void incTimeBase();
  void decTimeBase();

private:
  HantekDataSource * device_;
  QLabel * timeBaseLabel_;
  QDial  * timeBaseDial_;
};

#endif // TIMEBASECONTROL_H
