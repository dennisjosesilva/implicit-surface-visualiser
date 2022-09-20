#pragma once

#include <QMainWindow>
#include "MainWidget.hpp"


class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  MainWindow();

private:  
  MainWidget *mainWidget_;
};