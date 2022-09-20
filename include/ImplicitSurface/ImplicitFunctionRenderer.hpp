#pragma once 

// Implicit function rendering based on marching cube 
// marching cube based on the description of the method
// Alex's book

#include "Renderer.hpp"
#include "ImplicitSurface/ImplicitSurfaceMesh.hpp"
#include <QVector>

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class ImplicitFunctionRenderer : public Renderer 
{
public:
  using ImplicitSurfacePtr = std::shared_ptr<ImplicitSurfaceMesh>;

  ImplicitFunctionRenderer(QOpenGLFunctions *gl,
    CameraPtr camera, ImplicitSurfacePtr f);

  void updateVBOs();

  void initShaders() override;
  void initBuffers() override;

  void updateUniforms();

  void mouseMoveEvent(QMouseEvent *e);
  void mousePressEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);

  void wheelEvent(QWheelEvent *e);
  void keyPressEvent(QKeyEvent *e);

  void update() override;

  void draw() override;

private:
  ImplicitSurfacePtr meshSurface_;  

  QOpenGLVertexArrayObject vao_;
  QOpenGLBuffer coordsVBO_;
  QOpenGLBuffer normalsVBO_;
  QOpenGLBuffer indicesVBO_;

  uint32 uniModelViewMatrix_;
  uint32 uniProjectMatrix_;
  uint32 uniNormalMatrix_;

  QOpenGLShaderProgram shaderProgram_;
};