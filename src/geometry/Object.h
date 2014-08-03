#ifndef OBJECT_H
#define OBJECT_H

#include "../types.h"

#include "../renderer/Ray.h"
#include "../renderer/Color.h"
#include "../materials/Material.h"
#include "Intersection.h"

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

  /** Positioning */
  void moveTo(Point const & pos);
  void rotate(float rx, float ry, float rz);

  /**
   * @param ray
   * @param *intersection Object to write the intersection info to
   * @return Whether or not the ray crosses this object
   */
  // TODO: handle intersections computation in object coordinates
  virtual bool intersects(Ray const & ray, Intersection * intersection) = 0;

  Color getColor() const;
  void setColor(Color const & color);
  Material const & getMaterial() const;
  void setMaterial(Material const & material);

protected:
  /**
   * Amount to which by push back intersection points
   * in the direction of the normal.
   */
  static float const PUSH_BACK;

  /**
   * Transformation matrix
   * used to convert world coordinates to object coordinates
   */
  Eigen::Matrix4f worldMatrix;
};

#endif
