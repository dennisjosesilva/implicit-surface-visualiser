#pragma once 

#include <QVector3D>

#include <QVector>
#include <memory>


// ==============================================================
// IMPLICIT FUNCTION
// ==============================================================
class ImplicitFunction
{
public:
  virtual float apply(const QVector3D &p) = 0;
  float operator() (const QVector3D &p) { return apply(p); }
};

// ==============================================================
// SPHERE FUNCTION 
// ==============================================================
class SphereImplicitFunction : public ImplicitFunction
{
public:
  SphereImplicitFunction();
  float apply(const QVector3D &p) override;
};

// ==============================================================
// SKEL POINT IMPLICIT FUNCTION
// ==============================================================
class SkelPointImplicitFunction : public ImplicitFunction
{
public:
  SkelPointImplicitFunction(const QVector3D &skelPoint);

  float distance(const QVector3D &p) const;
  virtual float filter(float d) = 0;

  float apply(const QVector3D &p) override;

private:
  QVector3D skelPoint_;
};

// ==============================================================
// GLOBAL SKEL POINT IMPLICIT FUNCTION
// ==============================================================
class GlobalSkelPointImplicitFunction : public ImplicitFunction
{
public:
  using SkelPointImplicitFunctionPtr = std::shared_ptr<SkelPointImplicitFunction>;

  GlobalSkelPointImplicitFunction();
  GlobalSkelPointImplicitFunction(
    const QVector<SkelPointImplicitFunctionPtr> &skelPoints);

  float apply(const QVector3D &p) override;

  void addSkelPoint(SkelPointImplicitFunctionPtr skelPoint);
  void addSkelPoints(
    const QList<SkelPointImplicitFunctionPtr> &skelPoints);

private:
  QVector<SkelPointImplicitFunctionPtr> skelPoints_;
};

// ==============================================================
// BLINN IMPLICIT FUNCTION
// ==============================================================
class BlinnImplicitFunction : public SkelPointImplicitFunction
{
public:
  BlinnImplicitFunction(const QVector3D &skelPoint, float r);
  float filter(float d) override;

private:
  float r_;
};

// ==============================================================
// SOFT OBJECTS IMPLICIT FUNCTION
// ==============================================================
class SoftObjectsImplicitFunction : public SkelPointImplicitFunction
{
public:
  SoftObjectsImplicitFunction(const QVector3D &skelPoint, float r);
  float filter(float d) override;

private:
  float r_;
};

// ==============================================================
// METABALLS IMPLICIT FUNCTION
// ==============================================================
class MetaballsImplicitFunction : public SkelPointImplicitFunction
{
public:
  MetaballsImplicitFunction(const QVector3D &skelPoint, float r);
  float filter(float d) override;

private:
  float r_;
};

// ==============================================================
// WYVILL IMPLICIT FUNCTION
// ==============================================================
class WyvillImplicitFunction : public SkelPointImplicitFunction
{
public:
  WyvillImplicitFunction(const QVector3D &skelPoint, float r);
  float filter(float d) override;

private:
  float r_;
};