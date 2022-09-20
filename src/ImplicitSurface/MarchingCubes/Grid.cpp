#include "ImplicitSurface/MarchingCubes/Grid.hpp"

GridCell::GridCell()
{}

GridCell::GridCell(const std::array<QVector3D, 8> &verts, 
  const std::array<double, 8> &vals)
  : verts_{verts}, vals_{vals}
{}

Grid::Grid(ImplicitFunction f, const QVector3D &ftl, const QVector3D &bbr, 
  float cellSize)
  : f_{f},
    nx_{static_cast<int>((bbr.x() - ftl.x()) / cellSize)},
    ny_{static_cast<int>((ftl.y() - bbr.y()) / cellSize)},
    nz_{static_cast<int>((bbr.z() - ftl.z()) / cellSize)}
{
  // offsets (from the front top left corner)
  std::array<QVector3D, 8> offsets = {
    QVector3D{0.0f, -cellSize, cellSize},      // back bottom left corner (0)
    QVector3D{cellSize, -cellSize, cellSize},  // back bottom right corner (1)
    QVector3D{cellSize, -cellSize, 0.0f},      // front bottom right corner (2)
    QVector3D{0.0f, -cellSize, 0.0f},          // front bottom left corner (3)
    QVector3D{0.0f, 0.0f, cellSize},           // back top left corner (4)
    QVector3D{cellSize, 0.0f, cellSize},       // back top right corner (5)
    QVector3D{cellSize, 0.0f, 0.0f},           // front top right corner (6) 
    QVector3D{0.0f, 0.0f, 0.f}                 // front top left corner (7)
  };


  cells_.reserve(nx_*ny_*nz_);
  for (int z = 0; z < nz_; z++) {
    for (int y = 0; y < ny_; y++) {
      for (int x = 0; x < nx_; x++) {
        GridCell c;
        
        QVector3D cellTLF{
          ftl.x() + (x*cellSize),
          ftl.y() - (y*cellSize),
          ftl.z() + (z*cellSize) };

        for (int i = 0; i < offsets.size(); i++) {
          c.vertex(i) = cellTLF + offsets[i];
          c.val(i) = f_(c.vertex(i));
        }
        cells_.append(c);
      }
    }
  }  
}

void Grid::updateValues()
{
  for (GridCell &c : cells_) {
    for (int i = 0; i < c.vals().size(); ++i) {
      c.val(i) = f_(c.vertex(i));
    }
  }
}