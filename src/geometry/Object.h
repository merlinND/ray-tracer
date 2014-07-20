#ifndef OBJECT_H
#define OBJECT_H

#include "../types.h"

#include "../renderer/Ray.h"
#include "../renderer/Color.h"
#include "../materials/Material.h"
#include "Intersection.h"

// TODO: allow for rotations
// TODO: compute object -> scene coordinates matrix
// TODO: handle intersections computation in object coordinates
class Object {
public:
  Point position;
  Material material;

  /**
   * Value that we consider "close enough to zero"
   * when computing intersections
   */
  static float const EPSILON;

  /** Constructor */
  Object(Point const & pos, Material const & m);

  /**
   * @param ray
   * @param *intersection Object to write the intersection info to
   * @return Whether or not the ray crosses this object
   */
  virtual bool intersects(Ray const & ray, Intersection * intersection) = 0;

  Color getColor() const;
  void setColor(Color const & color);

protected:

};

#endif
