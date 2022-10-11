#pragma once 

#include <memory.h>

#include "PrimitiveMesh.hpp"
#include "Renderer.hpp"

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class PrimitiveRenderer : public Renderer
{
public:
  using MeshPtr = std::unique_ptr<PrimitiveMesh>;

  PrimitiveRenderer(QOpenGLFunctions_4_1_Core *gl, 
    CameraPtr camera, MeshPtr mesh);

  void initShaders() override;
  void initBuffers() override;

  void updateUniforms();

  void update() override;

  void draw() override;

private:
  MeshPtr mesh_;

  QOpenGLVertexArrayObject vao_;
  QOpenGLBuffer meshCoordsVBO_;
  QOpenGLBuffer meshNormalsVBO_;
  QOpenGLBuffer meshIndicesVBO_;

  uint32 uniModelViewMatrix_;
  uint32 uniProjectionMatrix_;
  uint32 uniNormalMatrix_;

  QOpenGLShaderProgram shaderProgram_;
};