#ifndef OBJECT_H
#define OBJECT_H

#include "../types.h"

#include "../renderer/Ray.h"
#include "../renderer/Color.h"
#include "../materials/Material.h"

// TODO: allow for rotations
// TODO: compute object -> scene coordinates matrix
// TODO: handle intersections computation in object coordinates
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

  Color getColor() const;

protected:
  /**
   * Value that we consider "close enough to zero"
   * when computing intersections
   */
  static float const EPSILON;

};

#endif
