#include <cfloat>

#include "Parallelepipoid.h"

Parallelepipoid::Parallelepipoid(Point const & p, float lx, float ly, float lz)
  : Object(p) {

  this->minBounds[0] = - (lx / 2);
  this->maxBounds[0] = + (lx / 2);
  this->minBounds[1] = - (ly / 2);
  this->maxBounds[1] = + (ly / 2);
  this->minBounds[2] = - (lz / 2);
  this->maxBounds[2] = + (lz / 2);
}

bool Parallelepipoid::computeIntersection(Ray const & ray, Intersection * intersection) {
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
    if(std::abs(ray.direction[i]) < Object::EPSILON) {
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
  Vec intersectionPosition = ray.from + (t * ray.direction);

  // Normal vector at this point
  intersection->normal = Vec(0, 0, 0);
  intersection->normal[axis] = 1;
  // Make sure the normal vector is on the same side as the origin of the ray
  if(ray.direction.dot(intersection->normal) > 0) {
    intersection->normal[axis] = -1;
  }

  // Push back the intersection point so as to avoid self-intersection
  intersection->position = intersectionPosition + Object::PUSH_BACK * intersection->normal;

  // Texture coordinates associated with the intersection point
  // Coordinate system local to the side on which the intersection happened
  uint ui = (axis+1) % 3;
  uint vi = (axis+2) % 3;
  Vec u(0, 0, 0), v(0, 0, 0);
  u[ui] = 1;
  v[vi] = 1;

  // Coordinates in this side
  // TODO: fix misalignment bug
  float x = 0.5f + (intersectionPosition.dot(u) / (this->maxBounds[ui] - this->minBounds[ui]));
  float y = 0.5f - (intersectionPosition.dot(v) / (this->maxBounds[vi] - this->minBounds[vi]));

  // Select the correct side in the texture
  // Numbering rule: adding two opposite face's index gives 5
  uint faceIndex = (intersectionPosition[axis] > 0 ? axis : 5 - axis);
  float xOffset = (faceIndex % 3) * (1 / 3.f);
  float yOffset = (faceIndex / 3) * (1 / 2.f);

  intersection->textureX = (x / 3.f) + xOffset;
  intersection->textureY = (y / 2.f) + yOffset;

  return true;
}
