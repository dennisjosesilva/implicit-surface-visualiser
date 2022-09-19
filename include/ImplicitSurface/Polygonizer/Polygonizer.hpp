#pragma once 

#include "ImplicitSurface/ImplicitFunction.hpp"

#include <memory>
#include <QVector3D>
#include <QVector>

#define HASHBIT    5
#define HASHSIZE   (size_t)(1<<3*HASHBIT)
#define MASK ((1<<HASHBIT)-1)
#define HASH(i,j,k)  (((i&BMASK)<<NBITS|j&BMASK)<<NBITS|(k&&BMASK))
#define BIT(i, bit) (((i)>>(bit))&1)
#define FLIP(i, bit) ((i)^1<<(bit))

namespace implicit
{
  struct Mesh
  {
    QVector<QVector3D> coords_;
    QVector<QVector3D> normals_;
  };

  struct Test 
  {
    QVector3D p;        /* point where the test was performed. */ 
    double value;       /* value of the function at p */
    bool ok;            /* value is of "correct" sign  */ 
  };

  class Polygonizer
  {
  private:
    static const int N_ITER_CONVERGENCY;

  public:
    enum Mode { TETRAHEDRAL, NON_TETRAHEDRAL };

    using ImplicitFunctionPtr = std::shared_ptr<ImplicitFunction>;

    Mesh polygonize();

  private:
    void makeCubeTable();
    Test find(bool isPosSign);
    QVector3D convergeToZeroCrossing(QVector3D p1, QVector3D p2, double v);

  private:
    std::shared_ptr<ImplicitFunction> f_;
    float size_;
    float delta_;  
    int bonds_;
    QVector3D startingPoint_;
    Mode mode_;
  };
}