#include "Cube.h"

Cube::Cube()
  : Object(Point(0, 0, 0), Material(Color(0.5, 0.5, 0.5))) {

}

bool Cube::intersects(Ray const & ray) {
  // TODO
  return true;
}
