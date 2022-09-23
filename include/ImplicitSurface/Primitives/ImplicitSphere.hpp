#pragma once 

#include "ImplicitSurface/ImplicitSurfaceMesh.hpp"


class ImplicitSphere : public ImplicitSurfaceMesh
{
public:
  ImplicitSphere(float radius=1.0f, float cellSize=0.20f);

  ImplicitFunction implicitFunction(float radius) const;
  GradImplicitFunction gradImplicitFunction(float radius) const; 

  ImplicitPrimitiveType type() const { return ImplicitPrimitiveType::SPHERE; }

};