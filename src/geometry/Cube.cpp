#include <cfloat>

#include "Cube.h"

Cube::Cube(Point const & p, float s)
  : Parallelepipoid(p, s, s, s), side(s) {
}
