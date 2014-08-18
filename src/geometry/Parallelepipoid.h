#ifndef PARALLELEPIPOID_H
#define PARALLELEPIPOID_H

#include "../types.h"
#include "Object.h"

class Parallelepipoid : public Object {
public:
  /**
   * @param p Position at which the object is centered
   * @param lx Length along the x axis (in meters)
   * @param ly Length along the y axis (in meters)
   * @param lz Length along the z axis (in meters)
   */
  Parallelepipoid(Point const & p, float lx, float ly, float lz);

protected:
  float minBounds[3];
  float maxBounds[3];

  virtual bool computeIntersection(Ray const & ray, Intersection * intersection);
};

#endif
