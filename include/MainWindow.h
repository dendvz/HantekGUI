/****************************************************************************
**
****************************************************************************/

#ifndef SCOPE_VIEW_H
#define SCOPE_VIEW_H

#include <QWidget>

class HantekDataSource;
class TimeBaseControl;
class ChannelControl;
class QGroupBox;

class MainWindow : public QWidget
{
  Q_OBJECT

public:
  MainWindow(QWidget * parent = 0);
  ~MainWindow();

public slots:
  void doAcquire();

private:
  HantekDataSource * device_;
  TimeBaseControl  * timeBaseControl_;
  std::vector<ChannelControl *> channelControl_;

  QGroupBox * createTriggerControl();
};

#endif // SCOPE_VIEW_H
