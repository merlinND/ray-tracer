#include "Plane.h"

Plane::Plane(Point const & p, Vec const & n)
  : Object(p), normal(n) {
}

bool Plane::computeIntersection(Ray const & ray, Intersection * intersection) {
  // TODO
  return false;
}
