#include "ImplicitSurface/Primitives/ImplicitTwoSkelPoints.hpp"
#include <cmath>

ImplicitTwoSkelPoints::ImplicitTwoSkelPoints(float R, float cellSize, float skelX)
  :ImplicitSurfaceMesh{
    implicitFunction(skelX, R),                              // implicit function
    QVector3D{-2.0f, 2.0f, -2.0f},                    // front top left corner of the bounding box
    QVector3D{2.0f, -2.0f, 2.0f},                     // back bottom right corner of the bounding box
    cellSize,                                         // cell size (marching cubes)
    0.5f                                              // iso-value 
  },
  skelX_{skelX}
{}

ImplicitTwoSkelPoints::ImplicitFunction
ImplicitTwoSkelPoints::implicitFunction(float skelX, float R) const 
{
  QVector3D s0{-skelX, 0.0f, 0.0f};
  QVector3D s1{ skelX, 0.0f, 0.0f};

  std::function<float (float)> g = [R](float d) { // Wyvill fall-off filter function
    if (d > R)
      return 0.0f;
    else 
      return powf(1.0f - (d*d)/(R*R), 3.0f);
  };

  return [g, s0, s1, R](const QVector3D &p){
    float d0 = p.distanceToPoint(s0);
    float d1 = p.distanceToPoint(s1);

    return g(d0) + g(d1);
  };
}