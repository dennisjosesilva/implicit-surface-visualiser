#pragma once 

#include "ImplicitSurface/ImplicitSurfaceMesh.hpp"

// Line skeleton primitive, distance surface appraoch.
class ImplicitLineSkel : public ImplicitSurfaceMesh
{
public:
  ImplicitLineSkel(float R=1.0f, float cellSize=0.05);

  ImplicitFunction implicitFunction(float R) const;

  ImplicitPrimitiveType type() const { return ImplicitPrimitiveType::LINE_SKEL; }
};