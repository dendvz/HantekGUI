#ifndef CHANNELCONTROL_H
#define CHANNELCONTROL_H

#include <QGroupBox>

class HantekDataSource;
class ChannelScaleSpinBox;

class ChannelControl : public QGroupBox
{
  Q_OBJECT
public:
  ChannelControl(QWidget * parent, int index, HantekDataSource * device);

signals:
  void valueChanged(int value);

public slots:
  void setScale(int value);

private slots:
  void onScaleValueChanged();

private:
  int channelIndex_;
  HantekDataSource * device_;
  ChannelScaleSpinBox * scale_;
};

#endif // CHANNELCONTROL_H
