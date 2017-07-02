#ifndef HELPERS_H
#define HELPERS_H

#include <QTime>
#include <QFileInfo>

#define TRACE(msg, ...) \
  qDebug("%s %s:%u %s() " msg, \
    QTime::currentTime().toString("HH:mm:ss.zzz").toStdString().c_str(), \
    QFileInfo(__FILE__).fileName().toStdString().c_str(), \
    __LINE__, __FUNCTION__, __VA_ARGS__)

#endif // HELPERS_H
