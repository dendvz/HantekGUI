#ifndef MARKER_H
#define MARKER_H

#include <QChartGlobal>
#include <QGraphicsItem>
#include <QFont>
#include <QColor>

class QGraphicsSceneMouseEvent;

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Marker : public QGraphicsObject
{
public:
  Marker(QChart * chart, QString text, QColor color, Qt::ArrowType direction);

  void setPosition(qreal position);
  void updateGeometry();

  QRectF boundingRect() const { return boundingRect_; }
  void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent * event);
  void mouseMoveEvent(QGraphicsSceneMouseEvent * event);

private:
  QString       text_;
  Qt::ArrowType direction_;
  QColor        color_;
  QRectF        boundingRect_;

    QRectF m_textRect;
    QPointF m_anchor;
    QFont m_font;
    QChart *m_chart;
};

#endif // MARKER_H
