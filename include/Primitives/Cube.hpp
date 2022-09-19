#pragma once 

#include "PrimitiveMesh.hpp"

class Cube : public PrimitiveMesh
{
public:
  Cube();

  uint32 numberOfIndices() const override { return indices_.size(); }

  const QVector<QVector3D> &vertCoords() const override;
  const QVector<QVector3D> &vertNormals() const override;
  const QVector<uint32> &indices() const override;

  ~Cube() {}

private:
  void createMesh();

private:
  QVector<QVector3D> vertCoords_;
  QVector<QVector3D> vertNormals_;
  QVector<uint32> indices_;
};