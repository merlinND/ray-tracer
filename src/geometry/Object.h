#ifndef OBJECT_H
#define OBJECT_H

#include "../types.h"

#include "../Ray.h"
#include "../materials/Material.h"

class Object {
public:
  Point position;
  Material material;

  /** Constructor */
  Object(Point const & pos, Material const & m);

  /**
   * @return Whether or not the ray crosses this object
   * @TODO Return the normal vector at point of intersection
   */
  virtual bool intersects(Ray const & ray) = 0;

protected:
  /**
   * Value that we consider "close enough to zero"
   * when computing intersections
   */
  static float const EPSILON;

};

#endif
