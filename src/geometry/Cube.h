#ifndef CUBE_H
#define CUBE_H

#include "../types.h"
#include "Object.h"

// TODO: generalize to any parallelepipoid
class Cube : public Object {
public:
  /** Length of a side */
  float side;

  /**
   * @param p Position at which the cube is centered
   * @param s Length of the side of the cube
   */
  Cube(Point const & p, float s);

protected:
  float minBounds[3];
  float maxBounds[3];

  virtual bool computeIntersection(Ray const & ray, Intersection * intersection);
};

#endif
