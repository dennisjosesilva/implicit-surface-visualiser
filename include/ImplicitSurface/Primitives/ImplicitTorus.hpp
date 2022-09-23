#pragma once 

#include "ImplicitSurface/ImplicitSurfaceMesh.hpp"

class ImplicitTorus : public ImplicitSurfaceMesh
{
public:
  ImplicitTorus(float outerRadius=1.0f, 
    float innerRadius=0.4f, float cellSize=0.25f);

  ImplicitFunction implicitFunction(float R, float r) const;
  GradImplicitFunction gradImplicitFunction(float R, float r) const;

  ImplicitPrimitiveType type() const { return ImplicitPrimitiveType::TORUS; }
};