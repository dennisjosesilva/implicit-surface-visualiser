#pragma once 

#include <memory>
// #include "ImplicitSurface/ImplicitFunction.hpp"
#include "ImplicitSurface/MarchingCubes/Polygonizer.hpp"
#include "alias.hpp"

#include <QMouseEvent>
#include <QScrollEvent>
#include <QKeyEvent>

// =============================================================================================
// Implicit surface mesh is a class that represent an implicit surface 
// polygonisation built upon CGAL 3D Surface mesh Generation example
// https://doc.cgal.org/latest/Surface_mesher/index.html#Chapter_3D_Surface_Mesh_Generation
// =============================================================================================

enum ImplicitPrimitiveType {
  SPHERE,
  TORUS,
  TWO_SKEL_POINTS
};

class ImplicitSurfaceMesh
{
public:
  using ImplicitFunction = Polygonizer::ImplicitFunction;
  using GradImplicitFunction = Polygonizer::GradImplicitFunction;

  ImplicitSurfaceMesh(ImplicitFunction f, 
    const QVector3D &tlf, const QVector3D &bbr,
    float cellSize, float isovalue=0.f);
  
  ImplicitSurfaceMesh(ImplicitFunction f,
    const QVector3D &tlf, const QVector3D &bbr,
    float cellSize, GradImplicitFunction fgrad, 
    float isovalue=0.0f);  

  void polygonize() { polygonizer_.polygonize(this); }

  const QVector<QVector3D> &vertCoords() const { return coords_; }
  const QVector<QVector3D> &vertNormals() const { return normals_; }

  QVector<QVector3D> &vertCoords() { return coords_; }
  QVector<QVector3D> &vertNormals() { return normals_; }

  bool hasChanged() const { return hasChanged_; }
  void setHasChanged(bool val) { hasChanged_ = val; }

  virtual void mouseMoveEvent(QMouseEvent *e){}
  virtual void mousePressEvent(QMouseEvent *e){}
  virtual void mouseReleaseEvent(QMouseEvent *e){}

  virtual void wheelEvent(QWheelEvent *e){}
  virtual void keyPressEvent(QKeyEvent *e){}

  virtual ImplicitPrimitiveType type() const = 0;

protected:
  Polygonizer polygonizer_;
  QVector<QVector3D> coords_;
  QVector<QVector3D> normals_;
  bool hasChanged_;
};