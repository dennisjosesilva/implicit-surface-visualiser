#pragma once 

#include "alias.hpp"
#include <QVector>
#include <QVector3D>

class PrimitiveMesh
{
public:
  PrimitiveMesh() {};

  virtual uint32 numberOfIndices() const = 0;

  virtual const QVector<QVector3D> &vertCoords() const = 0;
  virtual const QVector<QVector3D> &vertNormals() const = 0;
  virtual const QVector<uint32> &indices() const = 0;

  ~PrimitiveMesh() {};
};