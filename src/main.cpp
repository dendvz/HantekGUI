/****************************************************************************
**
****************************************************************************/

#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  app.setWheelScrollLines(1);

  MainWindow w;
  w.show();
    
  return app.exec();
}
