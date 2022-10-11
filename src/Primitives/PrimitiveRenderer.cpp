#include "Primitives/PrimitiveRenderer.hpp"

#include <QOpenGLVertexArrayObject>

#include <QDebug>

PrimitiveRenderer::PrimitiveRenderer(QOpenGLFunctions_4_1_Core *gl, 
  CameraPtr camera, MeshPtr mesh)
  : Renderer{gl, camera}, mesh_{std::move(mesh)},
    meshCoordsVBO_{QOpenGLBuffer::VertexBuffer},
    meshNormalsVBO_{QOpenGLBuffer::VertexBuffer},
    meshIndicesVBO_{QOpenGLBuffer::IndexBuffer}
{}

void PrimitiveRenderer::initShaders()
{ 
  shaderProgram_.create();
  shaderProgram_.addShaderFromSourceFile(QOpenGLShader::Vertex, 
    ":/shaders/primitives/simple.vs");
  shaderProgram_.addShaderFromSourceFile(QOpenGLShader::Fragment,
    ":/shaders/primitives/simple.fs");
  shaderProgram_.link();

  uniModelViewMatrix_ = shaderProgram_.uniformLocation("modelViewMatrix");
  uniProjectionMatrix_ = shaderProgram_.uniformLocation("projectionMatrix");
  uniNormalMatrix_ = shaderProgram_.uniformLocation("normalMatrix");
}

void PrimitiveRenderer::initBuffers()
{ 
  const QVector<QVector3D> &vertCoords = mesh_->vertCoords();
  const QVector<QVector3D> &vertNormals = mesh_->vertNormals();
  const QVector<uint32> &indices = mesh_->indices();
  
  shaderProgram_.bind();

  vao_.create();
  QOpenGLVertexArrayObject::Binder{&vao_};

  meshCoordsVBO_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  meshCoordsVBO_.create();
  meshCoordsVBO_.bind();  
  meshCoordsVBO_.allocate(vertCoords.constData(), vertCoords.count() * sizeof(QVector3D));
  shaderProgram_.setAttributeBuffer(0, GL_FLOAT, 0, 3, 0);
  shaderProgram_.enableAttributeArray(0);
  //meshCoordsVBO_.release();

  meshNormalsVBO_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  meshNormalsVBO_.create();
  meshNormalsVBO_.bind();
  meshNormalsVBO_.allocate(vertNormals.constData(), vertNormals.count() * sizeof(QVector3D));
  shaderProgram_.setAttributeBuffer(1, GL_FLOAT, 0, 3, 0);
  shaderProgram_.enableAttributeArray(1);
  //meshIndicesVBO_.release();

  meshIndicesVBO_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  meshIndicesVBO_.create();
  meshIndicesVBO_.bind();  
  meshIndicesVBO_.allocate(indices.constData(), indices.count() * sizeof(uint32));
  //meshIndicesVBO_.release();

  shaderProgram_.release();
}

void PrimitiveRenderer::updateUniforms()
{
  shaderProgram_.bind();
  shaderProgram_.setUniformValue(uniModelViewMatrix_, camera_->modelViewMatrix());
  shaderProgram_.setUniformValue(uniProjectionMatrix_, camera_->projectionMatrix());
  shaderProgram_.setUniformValue(uniNormalMatrix_, camera_->normalMatrix()) ;
  shaderProgram_.release();
}

void PrimitiveRenderer::update()
{
  if (camera_->isUniformUpdatedRequired()) {
    updateUniforms();    
    camera_->setUniformUpdatedRequired(false);
  }
}

void PrimitiveRenderer::draw()
{  
  shaderProgram_.bind();
  QOpenGLVertexArrayObject::Binder {&vao_};

  gl_->glDrawElements(GL_TRIANGLES, mesh_->numberOfIndices(), GL_UNSIGNED_INT, 0);
  
  shaderProgram_.release();
}