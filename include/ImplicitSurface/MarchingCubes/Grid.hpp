#pragma once 

#include <QVector3D>
#include <QVector>
#include <array>

#include "ImplicitSurface/ImplicitFunction.hpp"
#include <functional>

class GridCell 
{
public:
  GridCell();
  GridCell(const std::array<QVector3D, 8> &verts, 
    const std::array<double, 8> &vals);
  
  const std::array<QVector3D, 8> &verts() const { return verts_; }
  std::array<QVector3D, 8> &verts() { return verts_; }
  const QVector3D &vertex(int i) const { return verts_[i]; }
  QVector3D &vertex(int i) { return verts_[i]; }

  const std::array<double, 8> &vals() const { return vals_; }
  std::array<double, 8> &vals() { return vals_; }
  double val(int i) const { return vals_[i]; }
  double &val(int i) { return vals_[i]; }

private:
  std::array<QVector3D, 8> verts_;
  std::array<double, 8> vals_;
};

class Grid
{
public:
  using ImplicitFunction = std::function<float (const QVector3D &)>;

  Grid(ImplicitFunction f,
    const QVector3D &ftl, const QVector3D &bbr, float cellSize);

  int nx() const { return nx_; }
  int ny() const { return ny_; }
  int nz() const { return nz_; }

  int ncells() const { return nx_*ny_*nz_; }

  const QVector<GridCell>& cells() const { return cells_; }
  const GridCell &cell(int i) const { return cells_[i]; }
  const GridCell &cell(int ix, int iy, int iz) const;

  void updateImplicitFunction(ImplicitFunction f) { f_ = f; updateValues(); }

  void updateValues();

private:  
  QVector<GridCell> cells_;
  ImplicitFunction f_;
  int nx_;
  int ny_;
  int nz_;
};