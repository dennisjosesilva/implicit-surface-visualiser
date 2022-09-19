#pragma once

#include <QMainWindow>
#include "GraphicsViewWidget.hpp"


class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  MainWindow();

private:  
  GraphicsViewWidget *gview_;
};