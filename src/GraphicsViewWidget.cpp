#include "GraphicsViewWidget.hpp"

#include <QOpenGLContext>
#include <QOpenGLFunctions_4_1_Core>

#include "Primitives/PrimitiveRenderer.hpp"
#include "Primitives/Cube.hpp"

#include "ImplicitSurface/ImplicitFunctionRenderer.hpp"
#include "ImplicitSurface/ImplicitSurfaceMesh.hpp"

#include <cmath>

GraphicsViewWidget::GraphicsViewWidget(QWidget *parent)
  : QOpenGLWidget{parent}, isWireframeMode_{false},
    skelX_{0.600},
    step_{0.05}
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

  QOpenGLFunctions *gl = QOpenGLContext::currentContext()->functions();

  // Default camera 
  camera_ = std::make_shared<Camera>();

  // Default renderer
  // renderer_ = std::make_unique<PrimitiveRenderer>(gl, camera_, 
  //    std::make_unique<Cube>());
  
  // ImplicitFunctionPtr ifunctionPtr = std::make_shared<SphereImplicitFunction>();
  // renderer_ = std::make_unique<ImplicitFunctionRenderer>(gl, camera_,
  //   std::make_shared<ImplicitSurfaceMesh>(ifunctionPtr));    

  // ImplicitFunctionPtr ifunctionPtr = 
  //   std::make_shared<GlobalSkelPointImplicitFunction>(
  //     QVector<SkelPointImplicitFunction>({
  //       std::make_shared<WyvillImplicitFunction>(QVector3D(-2.0f, 0, 0), 1.0),
  //       std::make_shared<WyvillImplicitFunction>(QVector3D(+2.0f, 0, 0), 1.0)
  //     }));  

  // ImplicitFunction f = [](const QVector3D &p) {
  //   float d = QVector3D::dotProduct(p, p);
  //   return d - 1.0f;
  // };

  // GradImplicitFunction fgrad = [](const QVector3D &p) {
  //   return QVector3D{p.x()*2.0f, p.y()*2.0f, p.z()*2.0f};
  // };

  // skeletal primitive
  QVector3D s0{-skelX_, 0.0f, 0.0f};
  QVector3D s1{ skelX_, 0.0f, 0.0f};
  
  float r = 1.f;
  std::function<float (float)> g = [r](float d) {    
    return powf(1.0f - (d*d)/(r*r), 3.0f);
  };
  
  ImplicitFunction f = [&s0,&s1,&g,r](const QVector3D &p) {
    float d0 = p.distanceToPoint(s0);
    float d1 = p.distanceToPoint(s1);

    if (d0 > r && d1 > r)
      return 0.0f;
    else if (d0 > r) 
      return g(d1);
    else if (d1 > 1)
      return g(d0);
    else 
      return g(d0) + g(d1);
  };

  ImplicitSurfaceMeshPtr mesh = std::make_shared<ImplicitSurfaceMesh>(
    f,                                // implicit function
    QVector3D{-2.0f,  2.0f, -2.0f},   // front top left corner
    QVector3D{ 2.0f, -2.0f,  2.0f},   // back bottom right corner
    0.05f,                             // cell side size
    // fgrad,                            // gradient of f
    0.5f                              // isovalue
  );

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
  //renderer_->mouseMoveEvent(e);
  update();
}

void GraphicsViewWidget::mousePressEvent(QMouseEvent *e)
{
  camera_->mousePressEvent(e);
  //renderer_->mousePressEvent(e);
  update();
}

void GraphicsViewWidget::mouseReleaseEvent(QMouseEvent *e)
{
  camera_->mouseReleaseEvent(e);
}

void GraphicsViewWidget::wheelEvent(QWheelEvent *e)
{
  camera_->wheelEvent(e);
  //renderer_->wheelEvent(e);
  update();
}

void GraphicsViewWidget::keyPressEvent(QKeyEvent *e)
{
  using GlobalSkelPointImplicitFunctionPtr = 
    std::shared_ptr<GlobalSkelPointImplicitFunction>;
  using SkelPointImplicitFunction = 
    typename GlobalSkelPointImplicitFunction::SkelPointImplicitFunctionPtr;
  using ImplicitFunction = Polygonizer::ImplicitFunction;
  using GradImplicitFunction = Polygonizer::GradImplicitFunction;
  using ImplicitSurfaceMeshPtr = std::shared_ptr<ImplicitSurfaceMesh>;

  camera_->keyPressEvent(e);

  if (e->key() == Qt::Key_Plus) {
    skelX_ += step_;
    QVector3D s0{-skelX_, 0.0f, 0.0f};
    QVector3D s1{ skelX_, 0.0f, 0.0f};


    float r = 1.0f;
    std::function<float (float)> g = [r](float d) {      
      return powf(1.0f - (d*d)/(r*r), 3.0f);
    };

    ImplicitFunction f = [&s0,&s1,&g,r](const QVector3D &p) {
      float d0 = p.distanceToPoint(s0);
      float d1 = p.distanceToPoint(s1);

      if (d0 > r && d1 > r)
        return 0.0f;
      else if (d0 > r) 
        return g(d1);
      else if (d1 > 1)
        return g(d0);
      else 
        return g(d0) + g(d1);      
    };

    ImplicitSurfaceMeshPtr mesh = std::make_shared<ImplicitSurfaceMesh>(
      f,                                 // implicit function
      QVector3D{-2.0f,  2.0f, -2.0f},    // front top left corner
      QVector3D{ 2.0f, -2.0f,  2.0f},    // back bottom right corner
      0.05f,                             // cell side size
      // fgrad,                            // gradient of f
      0.5f                               // isovalue
    );

    dynamic_cast<ImplicitFunctionRenderer*>(renderer_.get())
      ->changeMesh(mesh);
  }
  else if (e->key() == Qt::Key_Minus) {
    skelX_ -= step_;
    QVector3D s0{-skelX_, 0.0f, 0.0f};
    QVector3D s1{ skelX_, 0.0f, 0.0f};

    float r = 1.0f;
    std::function<float (float)> g = [r](float d) {
      return powf(1.0f - (d*d)/(r*r), 3.0f);
    };

    ImplicitFunction f = [&s0,&s1,&g,r](const QVector3D &p) {
      float d0 = p.distanceToPoint(s0);
      float d1 = p.distanceToPoint(s1);

      if (d0 > r && d1 > r)
        return 0.0f;
      else if (d0 > r) 
        return g(d1);
      else if (d1 > 1)
        return g(d0);
      else 
        return g(d0) + g(d1);
    };

    ImplicitSurfaceMeshPtr mesh = std::make_shared<ImplicitSurfaceMesh>(
      f,                                // implicit function
      QVector3D{-2.0f,  2.0f, -2.0f},   // front top left corner
      QVector3D{ 2.0f, -2.0f,  2.0f},   // back bottom right corner
      0.05f,                             // cell side size
      // fgrad,                            // gradient of f
      0.5f                              // isovalue
    );

    dynamic_cast<ImplicitFunctionRenderer*>(renderer_.get())
      ->changeMesh(mesh);
  }

  switch (e->key())
  {
  case Qt::Key_W:
    isWireframeMode_ = !isWireframeMode_;   
    break;

  default:
    QOpenGLWidget::keyPressEvent(e);
  }

  //renderer_->keyPressEvent(e);
  update();
}