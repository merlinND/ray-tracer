#include <cfloat>

#include "Cube.h"

Cube::Cube(Point const & p, float s)
  : Object(p, Material(Color(0.5, 0.5, 0.5))), side(s) {

  float h = (s / 2);
  for(int i = 0; i < 3; ++i) {
    this->minBounds[i] = this->position[i] - h;
    this->maxBounds[i] = this->position[i] + h;
  }
}

bool Cube::intersects(Ray const & ray) {
  float tNear = FLT_MIN;
  float tFar = FLT_MAX;
  // Closest point of intersection of a bounding plane with the ray
  float t1;
  // Furthest point of intersection of a bounding plane with the ray
  float t2;

  for(int i = 0; i < 3; ++i) {
    float min = this->minBounds[i];
    float max = this->maxBounds[i];

    if(ray.direction[i] == 0) {
      if(ray.direction[i] <= min || ray.direction[i] >= max) {
        return false;
      }
    }
    else {
      t1 = (min - ray.from[i]) / ray.direction[i];
      t2 = (max - ray.from[i]) / ray.direction[i];

      if(t1 > t2) {
        float temp = t2;
        t2 = t1;
        t1 = temp;
      }
      if(t1 > tNear)
        tNear = t1;
      if(t2 < tFar)
        tFar = t2;

      if(tNear > tFar || tFar < Object::EPSILON) {
        return false;
      }
    }
  }

  // We've passed all the tests, there must be an intersection
  return true;
}
