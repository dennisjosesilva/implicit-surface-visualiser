#pragma once 

#include "ImplicitSurface/Polygonizer/CubeFace.hpp"
#include <QVector>

namespace implicit
{
  enum CubeTableEdgeSide : int
  {
    LB = 0,     // left bottom
    LT = 1,     // left top
    LN = 2,     // left near
    LF = 3,     // left far
    RB = 4,     // right bottom 
    RT = 5,     // right top 
    RN = 6,     // right near 
    RF = 7,     // right far
    BN = 8,     // bottom near
    BF = 9,     // bottom far
    TN = 10,    // top near
    TF = 11     // top far
  };

  class CubeTableEdge 
  {
  private:
    static const QVector<CubeFace> LeftFace_;
    static const QVector<CubeFace> RightFace_;
    static const QVector<CubeCorner> EndPoint1_;
    static const QVector<CubeCorner> EndPoint2_;


  public:
    CubeTableEdge() {}
    CubeTableEdge(CubeTableEdgeSide side);

    CubeTableEdgeSide side() const { return side_; }
    CubeCorner endpoint1() const { return EndPoint1_[side_]; }
    CubeCorner endpoint2() const { return EndPoint2_[side_]; }
    CubeFace leftFace() const { return LeftFace_[side_]; }
    CubeFace rightFace() const { return RightFace_[side_]; }

    bool operator==(CubeTableEdge other) { return other.side_ == side_; }
    bool operator!=(CubeTableEdge other) { return other.side_ != side_; }

  private:
    CubeTableEdgeSide side_;    
  };

  class CubeTable
  {
  public:
    using Edges = QVector<CubeTableEdge>;

    CubeTable();

  private:
    void makeCubeTable();
    QVector<CubeTableEdge> setupEdges() const;
    void codifyCubeConfig(int config, QVector<bool> &isPositive) const;
    bool isIntersectedEdge(CubeTableEdge edge, const QVector<bool> &isPositive) const;
    CubeFace otherFace(CubeTableEdge edge, CubeFace curFace) const;
    CubeTableEdge nextCWEdge(CubeTableEdge edge, CubeFace curFace) const;

  private:
    QVector<Edges> table_;
  };
}