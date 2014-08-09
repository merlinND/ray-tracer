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
  /**
   * @param rx Rotation around the x axis (in radians)
   * @param ry Rotation around the y axis (in radians)
   * @param rz Rotation around the z axis (in radians)
   */
  void rotate(float rx, float ry = 0, float rz = 0);

  /**
   * @param ray
   * @param *intersection Object to write the intersection info to
   * @return Whether or not the ray crosses this object
   */
  bool intersects(Ray const & ray, Intersection * intersection);

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
  Eigen::Matrix3f rotationMatrix;
  /**
   * A transposed copy of the rotation matrix,
   * pre-computed for performance.
   */
  Eigen::Matrix3f rotationMatrixT;
  /**
   * A simple flag which enables us to skip some matrix
   * multiplications if there's no rotation applied to this object.
   */
  bool hasRotation;

  /**
   * Actual intersection algorithm.
   * Needs to be implemented by each geometric object.
   */
   virtual bool computeIntersection(Ray const & ray, Intersection * intersection) = 0;
};

#endif
