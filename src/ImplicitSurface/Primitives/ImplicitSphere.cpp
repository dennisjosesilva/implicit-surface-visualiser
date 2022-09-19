#include "ImplicitSurface/Primitives/ImplicitSphere.hpp"

ImplicitSphere::ImplicitSphere(float radius, float cellSize)
  :ImplicitSurfaceMesh{
    implicitFunction(radius),  // implicit function 
    QVector3D{-radius-0.5f, radius+0.5f, -radius-0.5f},  // front top left corner bounding box
    QVector3D{radius+0.5f, -radius-0.5f, radius+0.5f},  // back bottom right corner bounding box
    cellSize,                                           // cell size
    gradImplicitFunction(radius),                       // gradient implicit function
    0.0f                                                // iso value
  }
{}

ImplicitSphere::ImplicitFunction ImplicitSphere::implicitFunction(float radius) const
{
  return [radius](const QVector3D &p) {
    return QVector3D::dotProduct(p, p) - radius;
  };
}

ImplicitSphere::GradImplicitFunction ImplicitSphere::gradImplicitFunction(float radius) const
{
  return [radius](const QVector3D &p) {
    return QVector3D{2.f*p.x(), 2.f*p.y(), 2.f*p.z()};
  };
}