/****************************************************************************
**
****************************************************************************/

#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  app.setWheelScrollLines(1);

  MainWindow mainWindow;
  mainWindow.show();
    
  return app.exec();
}
