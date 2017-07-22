#ifndef HELPERS_H
#define HELPERS_H

#include <QTime>
#include <QFileInfo>

#define APPLICATION_NAME "HantekGUI"

#define TRACE(msg, ...) \
  qDebug("%s %s:%u %s() " msg, \
    QTime::currentTime().toString("HH:mm:ss.zzz").toStdString().c_str(), \
    QFileInfo(__FILE__).fileName().toStdString().c_str(), \
    __LINE__, __FUNCTION__, __VA_ARGS__)

class QColor;
class QString;

QColor  rgbToColor(QString rgb);
QString colorToRgb(QColor color);

#endif // HELPERS_H
