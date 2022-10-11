#include "GraphicsViewWidget.hpp"

#include <QOpenGLContext>
#include <QOpenGLFunctions_4_1_Core>

#include "Primitives/PrimitiveRenderer.hpp"
#include "Primitives/Cube.hpp"

#include "ImplicitSurface/ImplicitFunctionRenderer.hpp"
#include "ImplicitSurface/ImplicitSurfaceMesh.hpp"

#include "ImplicitSurface/Primitives/ImplicitSphere.hpp"
#include "ImplicitSurface/Primitives/ImplicitTorus.hpp"
#include "ImplicitSurface/Primitives/ImplicitTwoSkelPoints.hpp"
#include <QOpenGLFunctions> 
#include <cmath>

GraphicsViewWidget::GraphicsViewWidget(QWidget *parent)
  : QOpenGLWidget{parent}, isWireframeMode_{false},
    skelX_{0.600},
    step_{0.05},
    shouldShowGrid_{false}
{}

void GraphicsViewWidget::initializeGL()
{
  // using ImplicitFunctionPtr = typename ImplicitSurfaceMesh::ImplicitFunctionPtr;
  using GlobalSkelPointImplicitFunctionPtr = 
    std::shared_ptr<GlobalSkelPointImplicitFunction>;
  using SkelPointImplicitFunction = 
    typename GlobalSkelPointImplicitFunction::SkelPointImplicitFunctionPtr;
  using ImplicitFunction = Polygonizer::ImplicitFunction;
  using GradImplicitFunction = Polygonizer::GradImplicitFunction;
  using ImplicitSurfaceMeshPtr = std::shared_ptr<ImplicitSurfaceMesh>;

  initializeOpenGLFunctions();

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  QOpenGLFunctions_4_1_Core *gl = context()->versionFunctions<QOpenGLFunctions_4_1_Core>();

  // Default camera 
  camera_ = std::make_shared<Camera>();

  ImplicitSurfaceMeshPtr mesh = std::make_shared<ImplicitTwoSkelPoints>();

  renderer_ = std::make_unique<ImplicitFunctionRenderer>(gl, camera_, mesh);  

  setFocusPolicy(Qt::FocusPolicy::StrongFocus);

  renderer_->initShaders();  
  renderer_->initBuffers();
  renderer_->update();
}

void GraphicsViewWidget::resizeGL(int newWidth, int newHeight)
{
  camera_->updateProjectionMatrix(newWidth, newHeight);
}

void GraphicsViewWidget::paintGL()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (isWireframeMode_)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else 
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  // TODO: set up wireframe mode
  renderer_->update();
  renderer_->draw();
}

void GraphicsViewWidget::mouseMoveEvent(QMouseEvent *e)
{
  camera_->mouseMoveEvent(e);
  renderer_->mouseMoveEvent(e);
  update();
}

void GraphicsViewWidget::mousePressEvent(QMouseEvent *e)
{
  camera_->mousePressEvent(e);
  renderer_->mousePressEvent(e);
  update();
}

void GraphicsViewWidget::mouseReleaseEvent(QMouseEvent *e)
{
  camera_->mouseReleaseEvent(e);
}

void GraphicsViewWidget::wheelEvent(QWheelEvent *e)
{
  camera_->wheelEvent(e);
  renderer_->wheelEvent(e);
  update();
}

void GraphicsViewWidget::keyPressEvent(QKeyEvent *e)
{
  switch (e->key())
  {
  case Qt::Key_W:
    isWireframeMode_ = !isWireframeMode_;   
    break;

  case Qt::Key_G: 
  {
    if (!shouldShowGrid_) {
      makeCurrent();
      renderer_->showMarchingCubeGrid();
      shouldShowGrid_ = true;
    }
    else {
      makeCurrent();
      renderer_->removeMarchingCubeGrid();
      shouldShowGrid_ = false;
    }
  }

  default:
    QOpenGLWidget::keyPressEvent(e);
  }

  renderer_->keyPressEvent(e);
  update();
}

void GraphicsViewWidget::changeImplicitPrimitive(ImplicitPrimitiveType type)
{  
  renderer_->changeMesh(type);
  update();
}