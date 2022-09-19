#pragma once

#include <QOpenGLWidget>
#include <QOpenGLDebugLogger>

#include "Renderer.hpp"

class GraphicsViewWidget : public QOpenGLWidget, QOpenGLFunctions
{
  Q_OBJECT
public:
  GraphicsViewWidget(QWidget *parent = nullptr);
  ~GraphicsViewWidget() {}

protected:
  void initializeGL() override;
  void resizeGL(int newWidth, int newHeight) override;
  void paintGL() override;

  void mouseMoveEvent(QMouseEvent *e);
  void mousePressEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);
  
  void wheelEvent(QWheelEvent *e);
  void keyPressEvent(QKeyEvent *e);

private:
  float skelX_;
  float step_;

  std::unique_ptr<Renderer> renderer_;
  std::shared_ptr<Camera> camera_;
  bool isWireframeMode_;
};
