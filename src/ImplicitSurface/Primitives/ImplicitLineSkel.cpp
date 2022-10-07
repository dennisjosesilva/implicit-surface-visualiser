#include "ImplicitSurface/Primitives/ImplicitLineSkel.hpp"
#include <cmath>
#include <QLineF>

#include <QDebug>

ImplicitLineSkel::ImplicitLineSkel(float R, float cellSize)
  :ImplicitSurfaceMesh{
    implicitFunction(R),
    QVector3D{-5.0f,  5.0f, -5.0f},
    QVector3D{ 5.0f, -5.0f,  5.0f},
    0.1f,
    0.5f}
{}

// point to line segment distance:
// implementation inspired by:
// https://math.stackexchange.com/questions/322831/determing-the-distance-from-a-line-segment-to-a-point-in-3-space
ImplicitLineSkel::ImplicitFunction
ImplicitLineSkel::implicitFunction(float R) const
{
  QVector3D e1{-1.0f, 0.0f, 0.0f}, e2{1.0f, 0.0f, 0.0f};
  QVector3D u = e2 - e1;

  std::function<float (float)> g = [R](float d) {
    if (d > R) 
      return 0.0f;
    else 
      return powf(1.0f - (d*d)/(R*R), 3.0f);
    return d;
  };

  float ulength = u.length();

  return [e1, e2, u, ulength, g](const QVector3D &p) {
    // compute vector of e1 to p
    QVector3D v = p - e1;

    // compute aux value to check if projection of p into u falls 
    // into the line segment.
    float aux = QVector3D::dotProduct(v, u) / ulength;

    if (aux < 0.0f) {
      // projection of p falls outside (e1,e2) line segment
      // closer to e1
      return g(p.distanceToPoint(e1));
    } 
    else if (aux > 1.0f) {
      // projection of p falls outside (e1,e2) line segment
      // closer to e2
      return g(p.distanceToPoint(e2));
    }
    else {
      // project p into the line (e1, e2) and
      // return the length of line segment defined by the projection
      QVector3D proj = e1 + aux*u;
      QVector3D projToP = p - proj;
      float val = g(projToP.length());
      qDebug() << projToP.length() << ", " << val;
      return g(projToP.length());
    }
  };
}