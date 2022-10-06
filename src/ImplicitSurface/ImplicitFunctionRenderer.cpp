#include "ImplicitSurface/ImplicitFunctionRenderer.hpp"

#include "ImplicitSurface/Primitives/ImplicitSphere.hpp"
#include "ImplicitSurface/Primitives/ImplicitTorus.hpp"
#include "ImplicitSurface/Primitives/ImplicitTwoSkelPoints.hpp"
#include "ImplicitSurface/Primitives/ImplicitLineSkel.hpp"

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
  meshSurface_->polygonize();
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

void ImplicitFunctionRenderer::changeMesh(ImplicitPrimitiveType type)
{    
  updateMesh(type);

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


void ImplicitFunctionRenderer::updateMesh(ImplicitPrimitiveType type)
{  
  switch (type)
  {
  case ImplicitPrimitiveType::SPHERE:         
    meshSurface_ = std::make_shared<ImplicitSphere>();
    break;
  
  case ImplicitPrimitiveType::TORUS: {
    std::shared_ptr<ImplicitSurfaceMesh> mesh = 
      std::make_shared<ImplicitTorus>();
    meshSurface_ = std::make_shared<ImplicitTorus>();    
    break;
  }
  case ImplicitPrimitiveType::TWO_SKEL_POINTS:
    meshSurface_ = std::make_shared<ImplicitTwoSkelPoints>();
    break;

  case ImplicitPrimitiveType::LINE_SKEL:
    meshSurface_ = std::make_shared<ImplicitLineSkel>();
    break;

  default:
    break;
  }  
}

void ImplicitFunctionRenderer::updateVBOs()
{
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
  meshSurface_->setHasChanged(false);

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

void ImplicitFunctionRenderer::mouseMoveEvent(QMouseEvent *e)
{
  meshSurface_->mouseMoveEvent(e);
}

void ImplicitFunctionRenderer::mousePressEvent(QMouseEvent *e)
{
  meshSurface_->mousePressEvent(e);
}

void ImplicitFunctionRenderer::mouseReleaseEvent(QMouseEvent *e)
{
  meshSurface_->mouseReleaseEvent(e);
}

void ImplicitFunctionRenderer::wheelEvent(QWheelEvent *e)
{
  meshSurface_->wheelEvent(e);
}

void ImplicitFunctionRenderer::keyPressEvent(QKeyEvent *e)
{
  meshSurface_->keyPressEvent(e);
}

void ImplicitFunctionRenderer::update()
{
  if (meshSurface_->hasChanged()) {
    updateVBOs();    
  }

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