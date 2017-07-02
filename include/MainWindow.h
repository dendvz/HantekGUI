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
class QGroupBox;
class QLabel;
class QDial;

class MainWindow : public QWidget
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

public slots:
  void doAcquire();
  void updateTimeBase(int tb);

private:
  QChart * chart_;
  std::vector<QLineSeries *> traces_;
  HantekDataSource * device_;

  // Timebase control (Horizontal)
  QLabel * timeBaseLabel_;
  QDial  * timeBaseDial_;

  QGroupBox * createHorizontalControl();
  QGroupBox * createTriggerControl();
  QGroupBox * createChannelControl(int ch);
};

#endif // SCOPE_VIEW_H
