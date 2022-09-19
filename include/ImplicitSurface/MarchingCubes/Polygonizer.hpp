#pragma once 

#include "ImplicitSurface/MarchingCubes/Grid.hpp"

#include <array>

class ImplicitSurfaceMesh;

class Polygonizer
{
public:
  using ImplicitFunction = Grid::ImplicitFunction;
  using GradImplicitFunction = 
    std::function<QVector3D(const QVector3D &)>;

  Polygonizer(ImplicitFunction f,
    const QVector3D &tlf, const QVector3D &bbr, 
    float cellSize, float isovalue=0.f);

  Polygonizer(ImplicitFunction f, 
    const QVector3D &tlf, const QVector3D &bbr,
    float cellSize, GradImplicitFunction fgrad, 
    float isovalue=0.0f);


void polygonize(ImplicitSurfaceMesh *mesh);

private:
  void polygonize(const GridCell &cell, 
    ImplicitSurfaceMesh *mesh);

  bool isLower(const QVector3D &l, const QVector3D &r) const;
  QVector3D interp(const QVector3D &p1, const QVector3D &p2, 
    float p1val, float p2val) const;

private:
  Grid grid_;
  float isoval_;
  std::function<float(const QVector3D &)> f_;
  std::function<QVector3D(const QVector3D &)> fgrad_;  
  std::array<int, 256> edgeTable_;
  std::array<std::array<int, 16>, 256> triTable_;
};

