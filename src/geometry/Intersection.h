#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "../types.h"
#include "../renderer/Ray.h"

// Forward declaration
extern class Object;

/**
 * Holds information about an intersection
 * between a Ray and an Object
 */
class Intersection {
public:
  Object const * object;
  Ray const * ray;
  /** Point of intersection */
  Point position;
  /** Normal vector computed at the point of intersection */
  Vec normal;

  Intersection();
  Intersection(Object const * object, Ray const * ray);

protected:
};

#endif
