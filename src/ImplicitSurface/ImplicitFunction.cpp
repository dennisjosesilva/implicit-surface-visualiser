#include "ImplicitSurface/ImplicitFunction.hpp"
#include <QtMath>


// ======================================================================
// SPHERE FUNCTION 
// ======================================================================
SphereImplicitFunction::SphereImplicitFunction()
{}

float SphereImplicitFunction::apply(const QVector3D &p)
{
  float d = QVector3D::dotProduct(p, p);
  return d - 1.0f;
}

// =====================================
// DISTANCE BASED IMPLICIT FUNCTION
// =====================================
SkelPointImplicitFunction::SkelPointImplicitFunction(
  const QVector3D &skelPoint)
  : skelPoint_{skelPoint}
{}

float SkelPointImplicitFunction::apply(const QVector3D &p)
{
  float r = distance(p);
  return filter(r);
}

float SkelPointImplicitFunction::distance(const QVector3D &p) const 
{
  return skelPoint_.distanceToPoint(p);
}

// ============================================================
// GLOBAL SKEL POINT IMPLICIT FUNCTION 
// ============================================================
GlobalSkelPointImplicitFunction::GlobalSkelPointImplicitFunction()
{}

GlobalSkelPointImplicitFunction::GlobalSkelPointImplicitFunction(
  const QVector<SkelPointImplicitFunctionPtr> &skelPoints)
  : skelPoints_{skelPoints}
{}

float GlobalSkelPointImplicitFunction::apply(const QVector3D &p)
{
  float total = 0.0f;
  for (SkelPointImplicitFunctionPtr s : skelPoints_) {
    total += s->apply(p);
  }

  return total;
}

void GlobalSkelPointImplicitFunction::addSkelPoint(
  SkelPointImplicitFunctionPtr skelPoint)
{
  skelPoints_.append(skelPoint);
}

void GlobalSkelPointImplicitFunction::addSkelPoints(
  const QList<SkelPointImplicitFunctionPtr> &skelPoints)
{
  for (SkelPointImplicitFunctionPtr s : skelPoints) {
    skelPoints_.append(s);
  }
  // skelPoints_.append(skelPoints);
}

// ==============================================
// BLINN IMPLICIT FUNCTION
// ==============================================
BlinnImplicitFunction::BlinnImplicitFunction(const QVector3D &skelPoint,
  float r)
  : SkelPointImplicitFunction{skelPoint}, r_{r}
{}

float BlinnImplicitFunction::filter(float d)
{
  return exp(-r_*(d*d));
}

// ==================================================
// SOFT OBJECTS IMPLICIT FUNCTION
// ==================================================
SoftObjectsImplicitFunction::SoftObjectsImplicitFunction(
  const QVector3D &skelPoint, float r)
  : SkelPointImplicitFunction{skelPoint}, r_{r}
{}

float SoftObjectsImplicitFunction::filter(float d)
{
  float d6 = pow(d,6), d4 = pow(d,4), d2 = pow(d, 2);
  float r6 = pow(r_,6), r4 = pow(r_,4), r2 = pow(r_, 2);
  
  float t1 = (4.f*d6) / (9.f*d4);
  float t2 = (17.f*d4) / (9.f*r4);
  float t3 = (22.f*d2) / (9.f*r2);
  
  return pow(1.0f - t1 + t2 - t3, 3);
}

// =====================================================
// METABALLS IMPLICIT FUNCTION
// =====================================================
MetaballsImplicitFunction::MetaballsImplicitFunction(
  const QVector3D &skelPoint, float r)
  : SkelPointImplicitFunction{skelPoint}, r_{r}
{}

float MetaballsImplicitFunction::filter(float d)
{
  if (0.0f <= d && d <= (r_/3))
    return 1.f - 3.f* pow(d/r_, 2);
  else if ((r_/3) <= d && d <= r_) 
    return (3.f/2.f)*pow(1.f - (d/r_), 2);
  else 
    return 0;
}

// =======================================================
// WYVILL IMPLICIT FUNCTION 
// =======================================================
WyvillImplicitFunction::WyvillImplicitFunction(
  const QVector3D &skelPoint, float r)
  : SkelPointImplicitFunction{skelPoint}, r_{r}
{}

float WyvillImplicitFunction::filter(float d)
{
  return pow(1 - ((d*d)/(r_*r_)), 3);
}