#include "Plane.h"

#include <iostream>
using namespace std;

Plane::Plane(Point const & p, Vec const & n)
  : Object(p), normal(n.normalized()) {
}

bool Plane::computeIntersection(Ray const & ray, Intersection * intersection) {
  Vec toSource = ray.from.normalized();
  Vec normal = this->normal;

  float cosSource = toSource.dot(normal);
  if(cosSource < 0) {
    // cout << "Got a vector coming from below" << endl;
    normal = -normal;
    cosSource *= -1;
  }

  float cosDirection = ray.direction.dot(normal);
  if(cosDirection > -Object::EPSILON) {
    // The ray is parallel or going away
    return false;
  }

  // We're now sure that there's an intersection
  // We allow to skip the computation of the intersection point
  if(intersection == NULL) {
    return true;
  }

  float t = (- ray.from.dot(normal) / cosDirection);
  intersection->position = (ray.from + t * ray.direction);
  intersection->normal = normal;

  // Push back the intersection point so as to avoid self-intersection
  intersection->position += Object::PUSH_BACK * intersection->normal;

  // Texture coordinates associated with the intersection point
  // Since we're on an infinite plane, the texture must repeat periodically
  Vec intersectionToCenter = Vec(this->position - intersection->position);
  int period = 10;
  // TODO: check
  intersection->textureX = ((int)intersectionToCenter[0] % period) / (float)period;
  intersection->textureY = ((int)intersectionToCenter[1] % period) / (float)period;

  return true;
}
