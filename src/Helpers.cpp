#include "Helpers.h"

#include <QString>
#include <QTextStream>
#include <QColor>

QColor rgbToColor(QString rgb)
{
  int value = 0;
  if (rgb.at(0) == '#' && rgb.length() == 7)
  {
    rgb.remove(0, 1);
    value = rgb.toInt(nullptr, 16);
  }
  return QColor(value);
}

QString colorToRgb(QColor color)
{
  QString ret("#");
  QTextStream str(&ret);

  str.setFieldWidth(2);
  str.setPadChar('0');
  str << hex << uppercasedigits << color.red() << color.green() << color.blue();
  return ret;
}
