#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../types.h"
#include "Object.h"

class Triangle : public Object {
public:
  /** Vertices */
  Point p1, p2, p3;

  /**
   */
  Triangle(Point const & vertex1, Point const & vertex2, Point const & vertex3);

protected:
  virtual bool computeIntersection(Ray const & ray, Intersection * intersection);
};

#endif
