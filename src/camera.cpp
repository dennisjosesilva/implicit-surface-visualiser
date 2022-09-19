#include "camera.hpp"

#include <QVector3D>
#include "global.hpp"
#include <QtMath>

#include <QDebug>

Camera::Camera(float FoV)
  :FoV_{FoV}, scale_{1.0f}, dragging_{false}
{}

void Camera::updateProjectionMatrix(int width, int height)
{
  float dispRatio = float(width) / float(height);

  projectionMatrix_.setToIdentity();
  projectionMatrix_.perspective(FoV_, dispRatio, 0.1f, 40.0f);

  updateMatrices();
}

void Camera::updateMatrices()
{
  modelViewMatrix_.setToIdentity();
  modelViewMatrix_.translate(QVector3D{0.0f, 0.0f, -3.0f});
  modelViewMatrix_.scale(scale_);
  modelViewMatrix_.rotate(rotation_);

  normalMatrix_ = modelViewMatrix_.normalMatrix();

  uniformUpdatedRequired_ = true;
}

void Camera::mouseMoveEvent(QMouseEvent *e)
{
  if (e->buttons() | Qt::LeftButton) {
    QVector2D sPos = toNormalizedScreenCoordinates(e->x(), e->y());
    QVector3D newRotVec = QVector3D{sPos.x(), sPos.y(), 0.0f};
    
    // project onto sphere
    float sqrZ = 1.0 - QVector3D::dotProduct(newRotVec, newRotVec);
    if (sqrZ > 0) {
      newRotVec.setZ(sqrt(sqrZ));
    }
    else {
      newRotVec.normalize();
    }

    QVector3D v2 = newRotVec.normalized();

    // reset if we are starting a drag    
    if (!dragging_) {
      dragging_ = true;
      oldRotVec = newRotVec;
      return;
    }

    // calculate axis and angle
    QVector3D v1 = oldRotVec.normalized();
    QVector3D N = QVector3D::crossProduct(v1, v2).normalized();
    if (N.length() == 0.0) {
      oldRotVec = newRotVec;
      return; 
    }

    float angle = 180.0f / M_PI * acos(QVector3D::dotProduct(v1, v2));
    rotation_ = QQuaternion::fromAxisAndAngle(N, angle) * rotation_;
    updateMatrices();

    // for next iteration
    oldRotVec = newRotVec;
  }
  else {
    dragging_ = false;
    oldRotVec = QVector3D{};
  }
}

void Camera::mousePressEvent(QMouseEvent *e)
{}

void Camera::mouseReleaseEvent(QMouseEvent *e)
{
  if (e->buttons() | Qt::LeftButton) {
    if (dragging_) {
      dragging_ = false;
      oldRotVec = QVector3D{};
    }
  }
}

void Camera::keyPressEvent(QKeyEvent *e)
{}

void Camera::wheelEvent(QWheelEvent *e)
{
  float phi = 1.0f + (e->angleDelta().y() / 2000.f);
  scale_ = fmin(fmax(phi * scale_, 0.01f), 100.0f);
  updateMatrices();
}