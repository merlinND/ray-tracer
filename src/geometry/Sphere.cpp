#include "../types.h"
#include "Sphere.h"

Sphere::Sphere(Point const & p, float r)
  : Object(p), radius(r), r2(r * r) {

}
bool Sphere::computeIntersection(Ray const & ray, Intersection * intersection) {
  // Determine if the origin of the ray is inside the sphere
  Vec toSphere = - ray.from;
  bool isInside = ((toSphere.squaredNorm() - this->r2) < Object::EPSILON);

  // Parameter corresponding to the orthogonal projection
  // of the sphere's center on the ray
  float tProjection = toSphere.dot(ray.direction);

  if(tProjection < Object::EPSILON && !isInside) {
    return false;
  }

  // Distance from the sphere's center to its projection on the ray
  float dProjection2 = (toSphere.squaredNorm() - tProjection * tProjection);

  // Length of the portion of ray from the intersection point
  // to the sphere's center projection
  float tToProjection2 = (this->r2 - dProjection2);

  if(tToProjection2 < Object::EPSILON) {
    return false;
  }

  // There's an intersection
  // Allow to skip the computation of the intersection point
  if(intersection == NULL) {
    return true;
  }

  // Parameter corresponding to the intersection point
  float t;
  if(isInside)
    t = tProjection + sqrt(tToProjection2);
  else
    t = tProjection - sqrt(tToProjection2);

  intersection->position = (ray.from + t * ray.direction);
  if(isInside) {
    intersection->normal = -intersection->position.normalized();
  }
  else {
    intersection->normal = intersection->position.normalized();
  }

  // Push back the intersection point so as to avoid self-intersection
  intersection->position += Object::PUSH_BACK * intersection->normal;

  return true;
}
