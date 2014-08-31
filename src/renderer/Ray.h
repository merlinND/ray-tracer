#ifndef RAY_H
#define RAY_H

#include <iostream>

#include "../types.h"

class Ray {
public:
  Point from;
  Vec direction;
  /**
   * Refraction index of the medium
   * at the starting point of this ray.
   */
  float refractionIndex;

  /** Constructor */
  Ray(Point f, Vec d, float n = Ray::DEFAULT_REFRACTION_INDEX);

protected:
  static float const DEFAULT_REFRACTION_INDEX;
};

/**
 * Pretty printing of rays
 */
inline std::ostream& operator<<(std::ostream& os, Ray const & r) {
  os << "from (" << r.from[0] << "," << r.from[1] << "," << r.from[2] << ")";
  os << " in direction ";
  os << "(" << r.direction[0] << "," << r.direction[1] << "," << r.direction[2] << ")";
  return os;
}

#endif
