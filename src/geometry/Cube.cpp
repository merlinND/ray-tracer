#include <cfloat>

#include "Cube.h"

Cube::Cube(Point const & p, float s)
  : Object(p, Material(Color(0.5, 0.5, 0.5))), side(s) {

  float h = (s / 2);
  for(int i = 0; i < 3; ++i) {
    this->minBounds[i] = this->position[i] - h;
    this->maxBounds[i] = this->position[i] + h;
  }
}

bool Cube::intersects(Ray const & ray) {
  // TODO
  return true;
}
