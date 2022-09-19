#include "MainWindow.hpp"

MainWindow::MainWindow()
{
  setWindowTitle("Implicit surface visualiser");

  gview_ = new GraphicsViewWidget{this};
  setCentralWidget(gview_);
}

