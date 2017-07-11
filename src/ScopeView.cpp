#include "ScopeView.h"
#include "Marker.h"
#include "Helpers.h"

#include <QtGui/QResizeEvent>
#include <QGraphicsScene>
#include <QLineSeries>
#include <QtWidgets/QGraphicsTextItem>
#include <QtGui/QMouseEvent>

#include <QChart>
#include <QChartView>
#include <QValueAxis>

class CustomAxis : public QValueAxis
{
public:
  CustomAxis(qreal min, qreal max, int divisions)
  {
    setRange(min, max);
    setLabelsVisible(false);
    setTickCount(divisions + 1);
    setMinorTickCount(4);
    setMinorGridLinePen(QPen(QBrush(QColor(255, 255, 255, 31)), 0, Qt::DotLine));
  }
};

ScopeView::ScopeView(QWidget *parent)
  : QGraphicsView(new QGraphicsScene, parent),
    chart_(new QChart)
{
  setDragMode(QGraphicsView::NoDrag);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  // chart
  chart_->legend()->hide();
  chart_->setBackgroundBrush(QColor(0, 0, 0));
  chart_->setMargins(QMargins(6, 10, 6, 10));

  chart_->addAxis(new CustomAxis(0, 2000, 10), Qt::AlignBottom);
  chart_->addAxis(new CustomAxis(0, 2000, 10), Qt::AlignTop);
  chart_->addAxis(new CustomAxis(-1, 1, 8),    Qt::AlignLeft);
  chart_->addAxis(new CustomAxis(-1, 1, 8),    Qt::AlignRight);

  chart_->setAcceptHoverEvents(true);

  setRenderHint(QPainter::Antialiasing);
  scene()->addItem(chart_);

  for (int trace = 0; trace < 2; ++trace)
  {
    traces_.push_back(new QLineSeries);
    // TODO: Load from settings
    QColor color;
    if (trace == 0)
    {
      color = QColor(255, 255, 0);
    }
    else
    {
      color = QColor(0, 255, 255);
    }
    traces_[trace]->setPen(color);
    chart_->addSeries(traces_[trace]);
    traces_[trace]->attachAxis(chart_->axisX());
    traces_[trace]->attachAxis(chart_->axisY());

    Marker * marker = new Marker(chart_, QString("CH%1").arg(trace + 1), color, Qt::RightArrow);
    markers_.append(marker);

    marker->setData(1, trace);
    marker->setPosition(0.5 - trace);
    connect(marker, SIGNAL(yChanged()), this, SLOT(markerPosChanged()));

//    connect(traces_[trace], SIGNAL(clicked(QPointF)), this, SLOT(keepMarker()));
  }

  this->setMouseTracking(true);
}

void ScopeView::resizeEvent(QResizeEvent *event)
{
  if (scene())
  {
    scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
    chart_->resize(event->size());
    foreach (Marker *marker, markers_)
    {
      marker->updateGeometry();
    }
  }
  QGraphicsView::resizeEvent(event);
}

void ScopeView::mouseMoveEvent(QMouseEvent *event)
{
  QGraphicsView::mouseMoveEvent(event);
}

void ScopeView::markerPosChanged()
{
  TRACE("%s", "WTF?");
}
