#include "Plane.h"

Plane::Plane(Point const & p, Vec const & n)
  : Object(p, Material(Color(1, 1, 1))), normal(n) {
}

bool Plane::intersects(Ray const & ray, Intersection * intersection) {
  // TODO
  return false;
}
