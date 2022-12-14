#pragma once 

#include "alias.hpp"
#include "camera.hpp"

#include <memory>

#include <QOpenGLFunctions>

#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>

class Renderer
{
public:
  using CameraPtr = std::shared_ptr<Camera>;

  Renderer(): gl_{nullptr} {}
  Renderer(QOpenGLFunctions *gl, CameraPtr camera);

  virtual void initShaders() = 0;
  virtual void initBuffers() = 0;

  virtual void update() = 0;

  virtual void draw() = 0;
  
  virtual void mouseMoveEvent(QMouseEvent *e);
  virtual void mousePressEvent(QMouseEvent *e);
  virtual void wheelEvent(QWheelEvent *e);
  virtual void keyPressEvent(QKeyEvent *e);

protected:
  QOpenGLFunctions *gl_;
  CameraPtr camera_;
};