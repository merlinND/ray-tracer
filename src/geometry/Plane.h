#ifndef PLANE_H
#define PLANE_H

#include "../types.h"
#include "Object.h"

class Plane : public Object {
public:
  /** Normal vector to this plane */
  Vec normal;

  /**
   * @param p One point of this plane
   * @param n Normal vector defining this plane
   */
  Plane(Point const & p, Vec const & n);


protected:
  virtual bool computeIntersection(Ray const & ray, Intersection * intersection);
};

#endif
