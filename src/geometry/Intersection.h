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
  /**
   * Texture (2D) coordinates corresponding to the point of intersection
   * ranging from 0 to 1.
   */
  float textureX, textureY;

  Intersection();
  Intersection(Object const * object, Ray const * ray, float s = 0, float t = 0);

protected:
};

#endif
