#pragma once 

#include "ImplicitSurface/ImplicitSurfaceMesh.hpp"

class ImplicitTwoSkelPoints : public ImplicitSurfaceMesh
{
public:
  ImplicitTwoSkelPoints(float R=1.0f, float cellSize=0.05, float skelX=0.6f);

  ImplicitFunction implicitFunction(float skelX, float R) const;

private:
  float skelX_;
};