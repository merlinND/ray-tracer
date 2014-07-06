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

bool Cube::intersects(Ray const & ray, Intersection * intersection) {
  float tNear = FLT_MIN;
  float tFar = FLT_MAX;
  // Closest point of intersection of a bounding plane with the ray
  float t1;
  // Furthest point of intersection of a bounding plane with the ray
  float t2;
  // Remember along which axis the collision happened
  uint axis;

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
      if(t1 > tNear) {
        tNear = t1;
        axis = i;
      }
      if(t2 < tFar) {
        tFar = t2;
        axis = i;
      }

      if(tNear > tFar || tFar < Object::EPSILON) {
        return false;
      }
    }
  }

  // We've passed all the tests, there must be an intersection
  float t;
  if(tNear > Object::EPSILON)
    t = tNear;
  else
    t = tFar;

  // Point of intersection
  intersection->position = ray.from + (t * ray.direction);

  // Normal vector at this point
  intersection->normal = Vec(0, 0, 0);
  intersection->normal[axis] = 1;
  // Make sure the normal vector points outwards
  // cos(theta) >= 0
  // TODO: check that this is correct
  Vec toI = (this->position - intersection->position);
  if(toI.normalized().dot(intersection->normal) >= 0) {
    intersection->normal[axis] = -1;
  }

  return true;
}
