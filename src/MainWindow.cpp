#include "MainWindow.hpp"

MainWindow::MainWindow()
{
  setWindowTitle("Implicit surface visualiser");

  mainWidget_ = new MainWidget{this};
  setCentralWidget(mainWidget_);
}

