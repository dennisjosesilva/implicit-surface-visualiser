#include "ImplicitSurface/Polygonizer/Polygonizer.hpp"

#include <random>

namespace implicit
{
  const int Polygonizer::N_ITER_CONVERGENCY = 10;


  /*
   isPosSign indicates if the function is looking for a point evaluated 
   to a positivity value (isPosSign = true) or negative (isPosSign = false)
  */
  Test Polygonizer::find(bool isPosSign)
  {
    const int NUM_TRIES = 10000;

    std::random_device r;
    std::default_random_engine re(r());
    std::uniform_real_distribution<float> dist(0, 1);

    Test test;
    double range = size_;
    test.ok = true;

    for (int i = 0; i < 10000; ++i) {
      test.p.setX(startingPoint_.x() + range * (dist(re) - 0.5f));
      test.p.setY(startingPoint_.y() + range * (dist(re) - 0.5f));
      test.p.setZ(startingPoint_.z() + range * (dist(re) - 0.5f));
      test.value = f_->apply(test.p);
      if (isPosSign == (test.value > 0.0))
        return test;
      range *= 1.0005; /* slowly expand search outwards */
    }
    test.ok = 0;
    return test;
  }

  QVector3D Polygonizer::convergeToZeroCrossing(QVector3D p1, QVector3D p2,
    double v)
  {
    QVector3D p;
    QVector3D pos, neg;

    if (v < 0) {
      pos.setX(p2.x()); pos.setY(p2.y()); pos.setZ(p2.z());
      neg.setX(p1.x()); neg.setY(p1.y()); neg.setZ(p1.z());
    }
    else {
      pos.setX(p1.x()); pos.setY(p1.y()); pos.setZ(p1.z());
      neg.setX(p2.x()); neg.setY(p2.y()); neg.setZ(p2.z());
    }

    for (int i = 0; i < N_ITER_CONVERGENCY; ++i) {
      p.setX(0.5 * (pos.x() + neg.x()));
      p.setY(0.5 * (pos.y() + neg.y()));
      p.setZ(0.5 * (pos.z() + neg.y()));

      if (f_->apply(p) > 0) {
        pos.setX(p.x()); pos.setY(p.y()); pos.setZ(p.z());              
      }
      else {
        neg.setX(p.x()); neg.setY(p.y()); neg.setZ(p.z());
      }
    }

    return p;
  }

  
}