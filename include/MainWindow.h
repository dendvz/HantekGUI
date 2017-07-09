/****************************************************************************
**
****************************************************************************/

#ifndef SCOPE_VIEW_H
#define SCOPE_VIEW_H

#include <QChartGlobal>
#include <QWidget>

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class HantekDataSource;
class TimeBaseControl;
class QGroupBox;

class MainWindow : public QWidget
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

public slots:
  void doAcquire();

private:
  QChart * chart_;
  std::vector<QLineSeries *> traces_;
  HantekDataSource * device_;
  TimeBaseControl  * timeBaseControl_;

  QGroupBox * createTriggerControl();
  QGroupBox * createChannelControl(int ch);
};

#endif // SCOPE_VIEW_H
