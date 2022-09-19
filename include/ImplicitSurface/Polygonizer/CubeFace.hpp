#pragma once 

namespace implicit
{
  enum CubeFace : int 
  {
    Left    = 0,   // -x
    Right   = 1,   // +x
    Bottom  = 2,   // -y
    Top     = 3,   // +y
    Near    = 4,   // -z
    Far     = 5    // +z
  };

  enum CubeCorner : int 
  {
    LBN = 0,     // left bottom near corner
    LBF = 1,     // left bottom far corner
    LTN = 2,     // left top near corner
    LTF = 3,     // left top far corner
    RBN = 4,     // right bottom near corner
    RBF = 5,     // right bottom far corner
    RTN = 6,     // right top near corner
    RTF = 7      // right top far corner
  };
}