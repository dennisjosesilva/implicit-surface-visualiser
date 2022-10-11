#pragma once

#include <QOpenGLWidget>
#include <QOpenGLDebugLogger>


#include "ImplicitSurface/ImplicitFunctionRenderer.hpp"

#include "ImplicitSurface/ImplicitSurfaceMesh.hpp"
#include <memory>

class GraphicsViewWidget : public QOpenGLWidget, QOpenGLFunctions_4_1_Core
{
  Q_OBJECT
public:
  GraphicsViewWidget(QWidget *parent = nullptr);
  ~GraphicsViewWidget() {}

  QSize sizeHint() const override { return QSize{720, 720}; }

  void changeImplicitPrimitive(ImplicitPrimitiveType type);

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

  std::unique_ptr<ImplicitFunctionRenderer> renderer_;
  std::shared_ptr<Camera> camera_;
  bool isWireframeMode_;
  bool shouldShowGrid_;
};
