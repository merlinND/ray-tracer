#ifndef RAY_H
#define RAY_H

#include <vector>

#include "types.h"

class Ray {
public:
  Point from;
  Vec direction;

  /** Constructor */
  Ray(Point f, Vec d);

protected:

};

#endif
