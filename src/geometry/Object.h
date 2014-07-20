#ifndef OBJECT_H
#define OBJECT_H

#include "../types.h"

#include "../renderer/Ray.h"
#include "../renderer/Color.h"
#include "../materials/Material.h"
#include "Intersection.h"

// TODO: allow for rotations
// TODO: compute object coordinates to scene coordinates matrix
// TODO: handle intersections computation in object coordinates
class Object {
public:
  Point position;
  Color color;
  Material const * material;

  // Default values
  static Color const DEFAULT_COLOR;
  static Material const & DEFAULT_MATERIAL;

  /**
   * Value that we consider "close enough to zero"
   * when computing intersections
   */
  static float const EPSILON;

  /** Constructor */
  Object(Point const & pos,
         Color const & c = Object::DEFAULT_COLOR,
         Material const & m = Object::DEFAULT_MATERIAL);

  /**
   * @param ray
   * @param *intersection Object to write the intersection info to
   * @return Whether or not the ray crosses this object
   */
  virtual bool intersects(Ray const & ray, Intersection * intersection) = 0;

  Color getColor() const;
  void setColor(Color const & color);
  Material const & getMaterial() const;
  void setMaterial(Material const & material);

protected:

};

#endif
