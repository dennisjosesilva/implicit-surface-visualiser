#pragma once 

#include <QVector2D>
#include <QApplication>
#include <QRect>
#include <QScreen>

QVector2D toNormalizedScreenCoordinates(int x, int y)
{
  float xRatio, yRatio;
  float xScene, yScene;
  QRect screenRect = QGuiApplication::primaryScreen()->geometry();


  xRatio = float(x)  / float(screenRect.width());
  yRatio = float(y) / float(screenRect.height());

  xScene = (1-xRatio)*-1 + xRatio*1;
  yScene = yRatio*-1 + (1-yRatio)*1;

  return QVector2D{xScene, yScene};
}