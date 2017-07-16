#include "Marker.h"
#include "Helpers.h"

#include <QPainter>
#include <QFontMetrics>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QChart>

static const int TIP_LENGTH = 5;

Marker::Marker(QChart * chart, QString text, QColor color, Qt::ArrowType direction)
  : QGraphicsObject(chart),
    text_(text),
    direction_(direction),
    color_(color),
    m_chart(chart)
{
  QFontMetrics metrics(m_font);
  m_textRect = metrics.boundingRect(text);
  prepareGeometryChange();
  switch (direction_)
  {
  case Qt::UpArrow:
    m_textRect.translate(2 * TIP_LENGTH, 5);  // FIXME
    boundingRect_ = m_textRect.adjusted(-5, 0, 2, 0);
    break;
  case Qt::DownArrow:
    m_textRect.translate(2 * TIP_LENGTH, 5);  // FIXME
    boundingRect_ = m_textRect.adjusted(-5, 0, 2, 0);
    break;
  case Qt::LeftArrow:
    m_textRect.translate(2 * TIP_LENGTH, 5);
    boundingRect_ = m_textRect.adjusted(-TIP_LENGTH, 0, 2, 0);
    break;
  case Qt::RightArrow:
    m_textRect.translate(- m_textRect.width() - 2 * TIP_LENGTH - 5, 5);
    boundingRect_ = m_textRect.adjusted(-2, 0, 5, 0);
    break;
  default:
    boundingRect_ = m_textRect;
    break;
  }
}

void Marker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QPainterPath path;

    qreal x0, y0, x1, y1, xT, yT;
    boundingRect_.getCoords(&x0, &y0, &x1, &y1);

    QVector<QPointF> points;
    switch (direction_)
    {
    case Qt::UpArrow:
      break;
    case Qt::DownArrow:
      break;
    case Qt::LeftArrow:
      xT = x0 - TIP_LENGTH;
      yT = (y0 + y1) / 2;
      points.push_back(QPointF(xT, yT));
      points.push_back(QPointF(x0, y1));
      points.push_back(QPointF(x1, y1));
      points.push_back(QPointF(x1, y0));
      points.push_back(QPointF(x0, y0));
      break;
    case Qt::RightArrow:
      xT = x1 + TIP_LENGTH;
      yT = (y0 + y1) / 2;
      points.push_back(QPointF(x0, y1));
      points.push_back(QPointF(x1, y1));
      points.push_back(QPointF(xT, yT));
      points.push_back(QPointF(x1, y0));
      points.push_back(QPointF(x0, y0));
      break;
    default:
      break;
    }

    path.addPolygon(QPolygonF(points));

//    QPointF anchor = mapFromParent(m_chart->mapToPosition(m_anchor));

    painter->setPen(color_);
    painter->setBrush(color_);
    painter->drawPath(path);
    painter->setPen(QColor(0, 0, 0));
    painter->drawText(m_textRect, text_);
}

void Marker::setPosition(qreal position)
{
  prepareGeometryChange();
  switch (direction_)
  {
  case Qt::UpArrow:
    break;
  case Qt::DownArrow:
    break;
  case Qt::LeftArrow:
    m_anchor = QPointF(2000, position);
    break;
  case Qt::RightArrow:
    m_anchor = QPointF(0, position);
    break;
  default:
    break;
  }
}

void Marker::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->setAccepted(true);
}

void Marker::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  if (event->buttons() & Qt::LeftButton)
  {
    QPointF offset = event->pos() - event->buttonDownPos(Qt::LeftButton);

    switch (direction_)
    {
    case Qt::UpArrow:
    case Qt::DownArrow:
      offset.setY(0);
      break;
    case Qt::LeftArrow:
    case Qt::RightArrow:
      offset.setX(0);
      break;
    default:
      break;
    }
    setPos(mapToParent(offset));
    event->setAccepted(true);
  }
  else
  {
    event->setAccepted(false);
  }
}

void Marker::updateGeometry()
{
  prepareGeometryChange();
  setPos(m_chart->mapToPosition(m_anchor));
}
