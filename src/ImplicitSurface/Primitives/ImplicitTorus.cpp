#include "ImplicitSurface/Primitives/ImplicitTorus.hpp"

#include <cmath>

ImplicitTorus::ImplicitTorus(float outerRadius, float innerRadius,
  float cellSize)
  :ImplicitSurfaceMesh{
    implicitFunction(outerRadius, innerRadius),
    QVector3D{-innerRadius-outerRadius-1.5f,  innerRadius+outerRadius+1.5f, -innerRadius-outerRadius-1.5f},
    QVector3D{ innerRadius+outerRadius+1.5f, -innerRadius-outerRadius-1.5f,  innerRadius+outerRadius+1.5f},
    cellSize,
    gradImplicitFunction(outerRadius, innerRadius),
    0.0f
  }
{}

ImplicitTorus::ImplicitFunction 
ImplicitTorus::implicitFunction(float R, float r) const 
{
  return [R,r](const QVector3D &p) {
    return powf(R - sqrtf(p.x()*p.x() + p.y()*p.y()), 2.0f) + p.z()*p.z() - r*r;
  };
}


ImplicitTorus::GradImplicitFunction
ImplicitTorus::gradImplicitFunction(float R, float r) const 
{
  return [R, r](const QVector3D &p) {
    return QVector3D{
      p.x() * (2.0f- (4.0f / sqrtf(p.x()*p.x() + p.y()*p.y()))),
      p.y() * (2.0f- (4.0f / sqrtf(p.x()*p.x() + p.y()*p.y()))),
      2.0f*p.z()};
  };
}