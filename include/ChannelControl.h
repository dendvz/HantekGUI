#ifndef CHANNELCONTROL_H
#define CHANNELCONTROL_H

#include <QGroupBox>

class HantekDataSource;
class SpinCombo;
class QCheckBox;

class ChannelControl : public QGroupBox
{
  Q_OBJECT
public:
  ChannelControl(QWidget * parent, int index, HantekDataSource * device);
  void set(int value);

signals:
  void valueChanged(int value);

private slots:
  void onValueChanged(int value);

private:
  int channelIndex_;
  HantekDataSource * device_;
  SpinCombo * voltage_;
  QCheckBox * probe_;
};

#endif // CHANNELCONTROL_H
