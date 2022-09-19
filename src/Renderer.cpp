#include "Renderer.hpp"


Renderer::Renderer(QOpenGLFunctions *gl, CameraPtr camera)
  :gl_{gl}, camera_{camera}
{}

void Renderer::mouseMoveEvent(QMouseEvent *e)
{}

void Renderer::mousePressEvent(QMouseEvent *e)
{}

void Renderer::wheelEvent(QWheelEvent *e)
{}

void Renderer::keyPressEvent(QKeyEvent *e)
{}