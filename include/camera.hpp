#pragma once 

#include <QMatrix4x4>
#include <QMatrix3x3>
#include <QQuaternion>

#include <QVector3D>

#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>

class Camera 
{
public:
  Camera(float FoV = 45.0f);
  bool isUniformUpdatedRequired() const { return uniformUpdatedRequired_; }
  void setUniformUpdatedRequired(bool val) { uniformUpdatedRequired_ = val; }
  
  void updateProjectionMatrix(int width, int height);

  void updateMatrices();

  void mouseMoveEvent(QMouseEvent *e);
  void mousePressEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);
  void wheelEvent(QWheelEvent *e);
  void keyPressEvent(QKeyEvent *e);

  const QMatrix4x4 &modelViewMatrix() const { return modelViewMatrix_; }
  const QMatrix4x4 &projectionMatrix() const { return projectionMatrix_; }
  const QMatrix3x3 &normalMatrix() const { return normalMatrix_; }

private:
  float FoV_;

  QMatrix4x4 modelViewMatrix_;
  QMatrix4x4 projectionMatrix_;
  QMatrix3x3 normalMatrix_;

  float scale_;
  QQuaternion rotation_;

  bool uniformUpdatedRequired_;

  QVector3D oldRotVec; 
  bool dragging_;
};