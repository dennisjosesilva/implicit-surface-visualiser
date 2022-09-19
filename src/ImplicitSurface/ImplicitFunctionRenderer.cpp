#include "ImplicitSurface/ImplicitFunctionRenderer.hpp"

ImplicitFunctionRenderer::ImplicitFunctionRenderer(
  QOpenGLFunctions *gl, CameraPtr camera, 
  ImplicitSurfacePtr meshSurface)
  : Renderer{gl, camera}, meshSurface_{meshSurface}
{}

void ImplicitFunctionRenderer::initShaders()
{
  shaderProgram_.create();
  shaderProgram_.addShaderFromSourceFile(QOpenGLShader::Vertex,
    ":/shaders/primitives/simple.vs");
  shaderProgram_.addShaderFromSourceFile(QOpenGLShader::Fragment,
    ":/shaders/primitives/simple.fs");
  shaderProgram_.link();

  uniModelViewMatrix_ = shaderProgram_.uniformLocation("modelViewMatrix");
  uniProjectMatrix_ = shaderProgram_.uniformLocation("projectionMatrix");
  uniNormalMatrix_ = shaderProgram_.uniformLocation("normalMatrix");
}

void ImplicitFunctionRenderer::initBuffers()
{
  const QVector<QVector3D> &vertCoords = meshSurface_->vertCoords();
  const QVector<QVector3D> &vertNormals = meshSurface_->vertNormals();
  // const QVector<uint32> &indices = meshSurface_->indices();

  shaderProgram_.bind();

  vao_.create();
  QOpenGLVertexArrayObject::Binder{&vao_};

  coordsVBO_.setUsagePattern(QOpenGLBuffer::DynamicDraw);
  coordsVBO_.create();
  coordsVBO_.bind();
  coordsVBO_.allocate(vertCoords.constData(), vertCoords.count() * sizeof(QVector3D));
  shaderProgram_.setAttributeBuffer(0, GL_FLOAT, 0, 3, 0);
  shaderProgram_.enableAttributeArray(0);

  normalsVBO_.setUsagePattern(QOpenGLBuffer::DynamicDraw);
  normalsVBO_.create();
  normalsVBO_.bind();
  normalsVBO_.allocate(vertNormals.constData(), vertNormals.count() * sizeof(QVector3D));
  shaderProgram_.setAttributeBuffer(1, GL_FLOAT, 0, 3, 0);
  shaderProgram_.enableAttributeArray(1);

  // indicesVBO_.setUsagePattern(QOpenGLBuffer::StaticDraw);
  // indicesVBO_.create();
  // indicesVBO_.bind();
  // indicesVBO_.allocate(indices.constData(), indices.count() * sizeof(uint32));

  shaderProgram_.release();
}

void ImplicitFunctionRenderer::changeMesh(ImplicitSurfacePtr mesh)
{
  meshSurface_ = mesh;

  const QVector<QVector3D> &vertCoords = meshSurface_->vertCoords();
  const QVector<QVector3D> &vertNormals = meshSurface_->vertNormals();
  // const QVector<uint32> &indices = meshSurface_->indices();

  shaderProgram_.bind();

  QOpenGLVertexArrayObject::Binder{&vao_};

  coordsVBO_.bind();
  coordsVBO_.allocate(vertCoords.constData(), vertCoords.count() * sizeof(QVector3D));

  normalsVBO_.bind();
  normalsVBO_.allocate(vertNormals.constData(), vertNormals.count() * sizeof(QVector3D));

  shaderProgram_.release();

  update();
}

void ImplicitFunctionRenderer::updateUniforms()
{
  shaderProgram_.bind();
  shaderProgram_.setUniformValue(uniModelViewMatrix_, camera_->modelViewMatrix());
  shaderProgram_.setUniformValue(uniProjectMatrix_, camera_->projectionMatrix());
  shaderProgram_.setUniformValue(uniNormalMatrix_, camera_->normalMatrix());
  shaderProgram_.release();
}

void ImplicitFunctionRenderer::update()
{
  if (camera_->isUniformUpdatedRequired()) {
    updateUniforms();
    camera_->setUniformUpdatedRequired(false);
  }
}

void ImplicitFunctionRenderer::draw()
{
  shaderProgram_.bind();
  QOpenGLVertexArrayObject::Binder {&vao_};

  gl_->glDrawArrays(GL_TRIANGLES, 0, meshSurface_->vertCoords().count());

  shaderProgram_.release();
}