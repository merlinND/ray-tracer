#include "../types.h"
#include "Sphere.h"

Sphere::Sphere(Point const & p, float r)
  : Object(p), radius(r) {

}
bool Sphere::intersects(Ray const & ray, Intersection * intersection) {
  float r2 = (this->radius * this->radius);

  // Determine if the origin of the ray is inside the sphere
  Vec toSphere = (this->position - ray.from);
  bool isInside = (toSphere.squaredNorm() < r2);

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
  float tToProjection2 = (r2 - dProjection2);

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
  if(isInside)
    intersection->normal = (this->position - intersection->position).normalized();
  else
    intersection->normal = (intersection->position - this->position).normalized();

  return true;
}
