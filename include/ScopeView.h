#ifndef SCOPEVIEW_H
#define SCOPEVIEW_H

#include <QtWidgets/QGraphicsView>
#include <QtCharts/QChartGlobal>

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

class QGraphicsScene;
class QMouseEvent;
class QResizeEvent;
class Marker;

QT_CHARTS_USE_NAMESPACE

class ScopeView: public QGraphicsView
{
  Q_OBJECT

public:
  ScopeView(QWidget *parent = 0);

  std::vector<QLineSeries *> getTraces() const { return traces_; }

protected:
  void resizeEvent(QResizeEvent * event);
  void mouseMoveEvent(QMouseEvent * event);

public slots:
  void markerPosChanged();

private:
  std::vector<QLineSeries *> traces_;

  QChart * chart_;

  QList<Marker *> markers_;
};

#endif // SCOPEVIEW_H
