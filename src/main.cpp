#include <QApplication>

#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
  QApplication app{argc, argv};

  MainWindow mainWindow;
  mainWindow.resize(720, 680);

  mainWindow.show();

  return app.exec();
}