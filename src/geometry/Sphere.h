#ifndef SPHERE_H
#define SPHERE_H

#include "../types.h"
#include "Object.h"

// TODO
class Sphere : public Object {
public:
  /** Radius (in meters) */
  float radius;

  /**
   * @param p Position at which the sphere is centered
   * @param r Radius of the sphere
   */
  Sphere(Point const & p, float r);

  virtual bool intersects(Ray const & ray, Intersection * intersection);

protected:
};

#endif
