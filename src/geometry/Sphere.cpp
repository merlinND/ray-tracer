#include <cfloat>

#include "Sphere.h"

Sphere::Sphere(Point const & p, float r)
  : Object(p, Material(Color(0.5, 0.5, 0.5))), radius(r) {

}
bool Cube::intersects(Ray const & ray, Intersection * intersection) {
  // TODO
}
