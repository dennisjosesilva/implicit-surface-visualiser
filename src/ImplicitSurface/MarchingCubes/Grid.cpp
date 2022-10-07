#include "ImplicitSurface/MarchingCubes/Grid.hpp"
#include <QList>

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

GridMesh Grid::genGridMesh() const
{
  // Initialise return GridMesh and initial vertex index
  GridMesh mesh;
  unsigned int idx = 0;
  
  mesh.vertcoords.reserve(8*cells_.size());
  mesh.indices.reserve(6*4*cells_.size());

  // compute the GL_LINE_LOOP mesh for each cell
  for (const GridCell &c : cells_) {
    // define cell vertex indices
    unsigned int i0 = idx,   i1 = idx+1, i2 = idx+2, i3 = idx+3,
                 i4 = idx+4, i5 = idx+5, i6 = idx+6, i7 = idx+7;     

    // push the vertex coords to the mesh
    mesh.vertcoords.append({
      c.vertex(0), c.vertex(1), c.vertex(2), c.vertex(3),
      c.vertex(4), c.vertex(5), c.vertex(6), c.vertex(7)});

    // include the indices of each border line for each 
    // face of the cell
    mesh.indices.append({i0, i1, i2, i3}); // bottom face
    mesh.indices.append({i4, i5, i6, i7}); // top face
    mesh.indices.append({i3, i2, i6, i7}); // front face
    mesh.indices.append({i4, i5, i1, i0}); // back face
    mesh.indices.append({i0, i3, i7, i4}); // left face
    mesh.indices.append({i1, i2, i6, i5}); // right face
    
    idx += 8;
  }
  
  return mesh;
}