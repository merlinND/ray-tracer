#ifndef SPHERE_H
#define SPHERE_H

#include "../types.h"
#include "Object.h"

class Sphere : public Object {
public:
  /** Radius (in meters) */
  float radius;
  /** Radius squared */
  float r2;

  /**
   * @param p Position at which the sphere is centered
   * @param r Radius of the sphere
   */
  Sphere(Point const & p, float r);

protected:
  virtual bool computeIntersection(Ray const & ray, Intersection * intersection);
};

#endif
