#include <cfloat>

#include "Cube.h"

Cube::Cube(Point const & p, float s)
  : Object(p, Material(Color(1, 1, 1))), side(s) {

  float h = (s / 2);
  for(int i = 0; i < 3; ++i) {
    this->minBounds[i] = this->position[i] - h;
    this->maxBounds[i] = this->position[i] + h;
  }
}

bool Cube::intersects(Ray const & ray, Intersection * intersection) {
  float tNear = FLT_MIN;
  float tFar = FLT_MAX;
  // Closest point of intersection of a bounding plane with the ray
  float t1;
  // Furthest point of intersection of a bounding plane with the ray
  float t2;
  // Remember along which axis the collision happened
  uint axisNear, axisFar;

  for(int i = 0; i < 3; ++i) {
    float min = this->minBounds[i];
    float max = this->maxBounds[i];

    // Ray parallel to this axis
    if(abs(ray.direction[i]) < Object::EPSILON) {
      if(ray.from[i] < min || ray.from[i] > max) {
        return false;
      }
    }
    // Ray not parallel
    else {
      t1 = (min - ray.from[i]) / ray.direction[i];
      t2 = (max - ray.from[i]) / ray.direction[i];

      if(t1 - t2 > Object::EPSILON) {
        float temp = t2;
        t2 = t1;
        t1 = temp;
      }
      if(t1 - tNear > Object::EPSILON) {
        tNear = t1;
        axisNear = i;
      }
      if(t2 - tFar < Object::EPSILON) {
        tFar = t2;
        axisFar = i;
      }

      if(tNear - tFar > Object::EPSILON || tFar < Object::EPSILON) {
        return false;
      }
    }
  }

  // We've passed all the tests, there must be an intersection
  // Allow to skip the computation of the intersection point
  if(intersection == NULL) {
    return true;
  }

  float t;
  uint axis;
  if(tNear > Object::EPSILON) {
    t = tNear;
    axis = axisNear;
  }
  else {
    t = tFar;
    axis = axisFar;
  }

  // Point of intersection
  intersection->position = ray.from + (t * ray.direction);

  // Normal vector at this point
  intersection->normal = Vec(0, 0, 0);
  intersection->normal[axis] = 1;
  // Make sure the normal vector is on the same side as the origin of the ray
  if((-ray.direction).dot(intersection->normal) < 0) {
    intersection->normal[axis] = -1;
  }

  // Push back the intersection point so as to avoid self-intersection
  intersection->position += Object::PUSH_BACK * intersection->normal;

  return true;
}
