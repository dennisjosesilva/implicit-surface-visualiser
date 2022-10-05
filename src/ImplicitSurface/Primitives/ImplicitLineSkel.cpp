#include "ImplicitSurface/Primitives/ImplicitLineSkel.hpp"

#include <QLineF>

ImplicitLineSkel::ImplicitLineSkel(float R, float cellSize)
  :ImplicitSurfaceMesh{
    implicitFunction(R),
    QVector3D{-2.0f,  2.0f, -2.0f},
    QVector3D{ 2.0f, -2.0f,  2.0f},
    cellSize,
    0.5f}
{}

ImplicitLineSkel::ImplicitFunction
ImplicitLineSkel::implicitFunction(float R) const
{
  QVector3D e1{-1.0f, -1.0f, -1.0f}, e2{1.0f, 1.0f, 1.0f};
  QLineF line{}

}