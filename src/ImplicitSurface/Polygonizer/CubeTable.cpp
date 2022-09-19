#include "ImplicitSurface/Polygonizer/CubeTable.hpp"
#include "ImplicitSurface/Polygonizer/HashMacros.hpp"

namespace implicit
{
  // ======================================================================
  // CUBE TABLE EDGE
  // ======================================================================
  
  const QVector<CubeCorner> CubeTableEdge::EndPoint1_ = { 
    CubeCorner::LBN, CubeCorner::LTN, CubeCorner::LBN, CubeCorner::LBF,
    CubeCorner::RBN, CubeCorner::RTN, CubeCorner::RBN, CubeCorner::RBF,
    CubeCorner::LBN, CubeCorner::LBF, CubeCorner::LTN, CubeCorner::LTF };

  const QVector<CubeCorner> CubeTableEdge::EndPoint2_ = {
    CubeCorner::LBF, CubeCorner::LTF, CubeCorner::LTN, CubeCorner::LTF,
    CubeCorner::RBF, CubeCorner::RTF, CubeCorner::RTN, CubeCorner::RTF,
    CubeCorner::RBN, CubeCorner::RBF, CubeCorner::RTN, CubeCorner::RTF };

  const QVector<CubeFace> CubeTableEdge::LeftFace_ = {
    CubeFace::Bottom,   CubeFace::Left,   CubeFace::Left,   CubeFace::Far, 
    CubeFace::Right,    CubeFace::Top,    CubeFace::Near,   CubeFace::Right,
    CubeFace::Near,     CubeFace::Bottom, CubeFace::Top,    CubeFace::Far };

  const QVector<CubeFace> CubeTableEdge::RightFace_ = {
    CubeFace::Left,   CubeFace::Top,   CubeFace::Near,  CubeFace::Left, 
    CubeFace::Bottom, CubeFace::Right, CubeFace::Right, CubeFace::Far, 
    CubeFace::Bottom, CubeFace::Far,   CubeFace::Near,  CubeFace::Top };

  CubeTableEdge::CubeTableEdge(CubeTableEdgeSide side)
    : side_{side}
  {}
  
  // ========================================================================
  // CUBE TABLE
  // ========================================================================
  CubeTable::CubeTable()
    :table_(256)
  {
    makeCubeTable();
  }

  void CubeTable::makeCubeTable()
  {
    QVector<bool> done(12);
    QVector<bool> isPositive(8);
    QVector<CubeTableEdge> edges = setupEdges();
    
    for (int i = 0; i < 256; i++) {
      done.fill(false);
      codifyCubeConfig(i, isPositive);
      for (CubeTableEdge e: edges) {
        if (!done[e.side()] && isIntersectedEdge(e, isPositive)) {

          CubeTableEdge start = e, edge = e;
          CubeFace face;
          if (isPositive[e.endpoint1()]) 
            face = e.rightFace();
          else
            face = e.leftFace();

          do {
            edge = nextCWEdge(edge, face);
            done[edge.side()] = true;
            if (isIntersectedEdge(edge, isPositive)) {
              table_[i].append(edge);
              face = otherFace(edge, face);
            }
          } while (edge != start);
        }
      }
    }
  }

  QVector<CubeTableEdge> CubeTable::setupEdges() const
  {
    QVector<CubeTableEdge> edges;
    edges.reserve(12);
    for (int e = 0; e < 12; e++)
      edges.append(CubeTableEdge{static_cast<CubeTableEdgeSide>(e)});
    
    return edges;
  }

  void CubeTable::codifyCubeConfig(int config, QVector<bool> &isPositive) const 
  {
    for (int c=0; c < 8; c++) 
      isPositive[c] = BIT(config, c);
  }

  bool CubeTable::isIntersectedEdge(CubeTableEdge edge, 
    const QVector<bool> &isPositive) const
  {
    return isPositive[edge.endpoint1()] != isPositive[edge.endpoint2()];
  }

  CubeFace CubeTable::otherFace(CubeTableEdge edge, CubeFace curFace) const 
  {
    CubeFace other = edge.leftFace();
    return other == curFace ? edge.rightFace() : other;
  }

  CubeTableEdge CubeTable::nextCWEdge(CubeTableEdge edge, CubeFace curFace) const
  {
    switch (edge.side()) {
      case CubeTableEdgeSide::LB: 
        return (curFace == CubeFace::Left) ? 
          CubeTableEdgeSide::LF : CubeTableEdgeSide::BF;
      
      case CubeTableEdgeSide::LT:
        return (curFace == CubeFace::Left) ? 
          CubeTableEdgeSide::LN : CubeTableEdgeSide::TF;      

     	case CubeTableEdgeSide::LN: 
        return (curFace == CubeFace::Left)? 
          CubeTableEdgeSide::LB : CubeTableEdgeSide::TN;
      
	    case CubeTableEdgeSide::LF: 
        return (curFace == CubeFace::Left)? 
          CubeTableEdgeSide::LT : CubeTableEdgeSide::BF;
      
      case CubeTableEdgeSide::RB: 
        return (curFace == CubeFace::Right)? 
          CubeTableEdgeSide::RN : CubeTableEdgeSide::BF;
      
      case CubeTableEdgeSide::RT: 
        return (curFace == Right)? 
          CubeTableEdgeSide::RF : CubeTableEdgeSide::TN;

      case CubeTableEdgeSide::RN: 
        return (curFace == CubeFace::Right)? 
          CubeTableEdgeSide::RT : CubeTableEdgeSide::BN;
      
	    case CubeTableEdgeSide::RF: 
        return (curFace == CubeFace::Right)? 
          CubeTableEdgeSide::RB : CubeTableEdgeSide::TF;
      
	    case CubeTableEdgeSide::BN: 
        return (curFace == CubeFace::Bottom)? 
          CubeTableEdgeSide::RB : CubeTableEdgeSide::LN;
      
	    case CubeTableEdgeSide::BF: 
        return (curFace == CubeFace::Bottom)? 
          CubeTableEdgeSide::LB : CubeTableEdgeSide::RF;
	    
      case CubeTableEdgeSide::TN: 
        return (curFace == CubeFace::Top)? 
          CubeTableEdgeSide::LT : CubeTableEdgeSide::RN;
    
	    case CubeTableEdgeSide::TF: 
        return (curFace == CubeFace::Top)? 
          CubeTableEdgeSide::RT : CubeTableEdgeSide::LF;
    }
    return CubeTableEdgeSide::LT;
  }
}