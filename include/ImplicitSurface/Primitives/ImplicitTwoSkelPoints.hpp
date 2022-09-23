#pragma once 

#include "ImplicitSurface/ImplicitSurfaceMesh.hpp"

class ImplicitTwoSkelPoints : public ImplicitSurfaceMesh
{
public:
  ImplicitTwoSkelPoints(float R=1.0f, float cellSize=0.05, float skelX=0.9f);

  ImplicitFunction implicitFunction(float skelX, float R) const;

  void keyPressEvent(QKeyEvent *e) override;

  ImplicitPrimitiveType type() const { return ImplicitPrimitiveType::TWO_SKEL_POINTS; }

private:
  void clear();

private:
  float skelX_;
  float R_;  
};